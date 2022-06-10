#include <unistd.h>
#include <stdio.h>
#include "my_malloc.h"

static Header base;
static Header *free_list = NULL;

void *Malloc(unsigned int nbytes) {
    Header *p,*prev;
    unsigned int nunits;
    
    nunits = (nbytes + sizeof(Header)-1)/sizeof(Header)+1;
    if((prev=free_list) == NULL) {
        base.s.next = free_list = prev = &base;
        base.s.size = 0;
    }

    for(p = prev->s.next;;prev = p,p = p->s.next) {
        if(p->s.size >nunits) {
            if(p->s.size =nunits) {
                prev->s.next = p->s.next;
            } else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            free_list = prev;
            return (void *)(p+1);
        }
        if (p == free_list) {
            if( (p=morecore(nunits) )==NULL) {
                return NULL;
            }

        }
    }
}

static Header *morecore(unsigned int nu) {
    char *cp;
    Header *up;
    if(nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu*sizeof(Header));
    if(cp==(char *)(-1)) {
        perror("sbrk error!");
        return NULL;
    }
    printf("sbrk:%p--%p\n",cp,cp+nu*sizeof(Header));
    
    up = (Header *)cp;
    up->s.size = nu;
    
    Free(up + 1);
    return free_list;
}

void Free(void *ap) {
    Header *bp,*p;
    bp = (Header *)ap -1;
    for(p = free_list;!(bp>p && bp<p->s.next);p = p->s.next)
    {
        if(p >= p->s.next && (bp>p || bp < p->s.next)) {
            break;
        }
    }

    if(bp + bp->s.size == p->s.next) {
        bp->s.size += p->s.next->s.size;
        bp->s.next = p->s.next->s.next;
    }
    else {
        bp->s.next = p->s.next;
    }

    if(p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.next = bp->s.next;
    }
    else {
        p->s.next = bp;
    }
}

void printlist(void) {
    Header *p;
    printf("free_list:");
    p = base.s.next;
    do {
        printf("%p:%d-->",p ,p->s.size );
        p = p->s.next;
    } while(p != &base);
    printf("\n");
}
