#include "co.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <setjmp.h>
#include <assert.h>

#define K (1024)
#define STACK_SIZE    (64 * K)

enum co_status {
    CO_NEW = 1,
    CO_RUNNING,
    CO_WAITING,
    CO_DEAD,
};

struct co {
    char*  name;
    void   (*func)(void*);
    void*  arg;

    enum co_status status;
    struct co*     waiter;
    struct co*     next;
    struct co*     previous;
    jmp_buf        context;
    unsigned char  stack[STACK_SIZE];
};

struct co* current = NULL;

__attribute__ ((section(".text"))) uint8_t bytecode[] = {
// make bytecode
#ifdef __x86_64__
// (void *sp /*rdi*/, void *entry /*rsi*/, uintptr_t arg /*rdx*/)
    0x58,                      // pop    %rax
    0x48, 0x89, 0xe1,          // mov    %rsp,%rcx
    0x48, 0x89, 0xfc,          // mov    %rdi,%rsp
    0x51,                      // push   %rcx      ; save (SP, PC)
    0x50,                      // push   %rax
    0x48, 0x89, 0xd7,          // mov    %rdx,%rdi
    0xff, 0xd6,                // callq  *%rsi
    0x58,                      // pop    %rax      ; restore (PC, SP)
    0x5c,                      // pop    %rsp
    0xff, 0xe0,                // jmpq   *%rax
    0xcc,                      // int3   
#else
// (void *sp, void *entry, uintptr_t arg)
// |     arg     | esp + 12
// |    entry    | esp + 8
// |     sp      | esp + 4
// | return addr | <- esp
    0x89, 0xe1,                // mov    %esp,%ecx
    0x8b, 0x01,                // mov    (%ecx),%eax
    0x8b, 0x61, 0x04,          // mov    0x4(%ecx),%esp
    0x51,                      // push   %ecx
    0x50,                      // push   %eax
    0x8b, 0x41, 0x0c,          // mov    0xc(%ecx),%eax
    0x50,                      // push   %eax
    0x8b, 0x41, 0x08,          // mov    0x8(%ecx),%eax
    0xff, 0xd0,                // call   *%eax
    0x58,                      // pop    %eax
    0x58,                      // pop    %eax
    0x5c,                      // pop    %esp
    0x59,                      // pop    %ecx
    0xff, 0xe0,                // jmp    *%eax
    0xcc,                      // int3
#endif
};

void (*stack_switch_call)(void *sp, void *entry, uintptr_t arg) = (void*)(bytecode);


struct co *co_start(const char *name, void (*func)(void *), void *arg) {
    struct co* new_co = malloc(sizeof(struct co));
    new_co->name = (char*)name;
    new_co->func = func;
    new_co->arg  = arg;
    new_co->status = CO_NEW;
    new_co->waiter = NULL;
    
    if (current == NULL) { // co_init of main
        current = new_co;
        current->next = new_co;
        current->previous = new_co;
    } else {
        struct co* previous = current->previous;
        new_co->previous = previous;
        new_co->next = current;
        previous->next = new_co;
        current->previous = new_co;
    }

    return new_co;
}

void co_wait(struct co *co) {
    while (co->status != CO_DEAD) {
        co->waiter = current;
        current->status = CO_WAITING;
        co_yield();
    }
    assert (co->status == CO_DEAD);
    assert (current->status != CO_WAITING);
    
    // remove co 
    assert(co->next != co);
    assert(co->previous != co);
    struct co* previous = co->previous;
    struct co* next = co->next;
    
    previous->next = next;
    next->previous = previous;

    free(co);
}

void co_yield() {
    int ret = setjmp(current->context);

    if (ret != 0) {  // returned from other saved context.
        return;      // do nothing; just return.
    }

select:
    do {
        current = current->next;
    } while (current->status != CO_NEW && current->status != CO_RUNNING);

    if (current->status == CO_NEW) {
        current->status = CO_RUNNING;
        stack_switch_call(
            &current->stack[STACK_SIZE], 
            current->func, 
            (uintptr_t)current->arg
        );
        current->status = CO_DEAD;
        if (current->waiter)
            current->waiter->status = CO_RUNNING;
        goto select;
    } else {
        longjmp(current->context, 42);
    }
}

static __attribute__((constructor)) void constructor() {
    current = co_start("main", NULL, NULL);
    current->status = CO_RUNNING;
}

static __attribute__((destructor)) void destructor() {
	struct co *previous, *next;
    if(current == NULL)
        return;
    while (current->next != current) {
        previous = current->previous;
        next = current->next;
        previous->next = next;
        next->previous = previous;
        free(current);
        current = next;
    }
    free(current);
    current = NULL;
}

int count = 1;
void entry(void *arg) {
    for (int i = 0; i < 5; i++) {
        printf("%s[%d] ", (const char *)arg, count++);
        co_yield();
    }
}

int main() {
    struct co *co1 = co_start("co1", entry, "a");
    struct co *co2 = co_start("co2", entry, "b");
    co_wait(co1);
    co_wait(co2);
    printf("Done\n");
}