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
#ifdef __x86_64__
    0x48, 0x8b, 0x0c, 0x24, // mov    (%rsp),%rcx
    0x48, 0x89, 0xe0,       // mov    %rsp,%rax
    0x48, 0x89, 0xfc,       // mov    %rdi,%rsp
    0x51,                   // push   %rcx         ; save (RBX, RBP, R12-R15) (SP, PC)
    0x50,                   // push   %rax
    0x41, 0x57,             // push   %r15
    0x41, 0x56,             // push   %r14
    0x41, 0x55,             // push   %r13
    0x41, 0x54,             // push   %r12
    0x55,                   // push   %rbp
    0x53,                   // push   %rbx
    0x48, 0x89, 0xd7,       // mov    %rdx,%rdi
    0xff, 0xd6,             // callq  *%rsi        ; entry(arg) 
    0x5b,                   // pop    %rbx         ; restore (RBX, RBP, R12-R15) (SP, PC)
    0x5d,                   // pop    %rbp
    0x41, 0x5c,             // pop    %r12
    0x41, 0x5d,             // pop    %r13
    0x41, 0x5e,             // pop    %r14
    0x41, 0x5f,             // pop    %r15
    0x58,                   // pop    %rax
    0x59,                   // pop    %rcx
    0x48, 0x89, 0xc4,       // mov    %rax,%rsp
    0x58,                   // pop    %rax
    0xff, 0xe1,             // jmpq   *%rcx
    0xcc, 0xcc, 0xcc        // breakpoint
#else
    0x89, 0xe0,             // mov    %esp,%eax
    0x8b, 0x10,             // mov    (%eax),%edx
    0x8b, 0x60, 0x04,       // mov    0x4(%eax),%esp
    0x52,                   // push   %edx         ; save (BX, SI, DI, BP) (SP, PC)
    0x50,                   // push   %eax
    0x55,                   // push   %ebp
    0x57,                   // push   %edi
    0x56,                   // push   %esi
    0x53,                   // push   %ebx
    0x8b, 0x50, 0x0c,       // mov    0xc(%eax),%edx
    0x52,                   // push   %edx
    0x8b, 0x50, 0x08,       // mov    0x8(%eax),%edx
    0xff, 0xd2,             // call   *%edx        ; entry(arg)
    0x5a,                   // pop    %edx         ; restore (BX, SI, DI, BP) (SP, PC)
    0x5b,                   // pop    %ebx
    0x5e,                   // pop    %esi
    0x5f,                   // pop    %edi
    0x5d,                   // pop    %ebp
    0x58,                   // pop    %eax
    0x5a,                   // pop    %edx
    0x89, 0xc4,             // mov    %eax,%esp
    0x58,                   // pop    %eax
    0xff, 0xe2,             // jmp    *%edx
    0xcc, 0xcc              // breakpoint 
#endif
};

void (*stack_switch_call)(void *sp /*rdi*/, void *entry /*rsi*/, uintptr_t arg /*rdx*/) = (void*)(bytecode);


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