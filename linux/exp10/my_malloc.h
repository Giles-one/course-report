#ifndef MY_MALLOC_H_
#define MY_MALLOC_H_

#include <stdlib.h>
typedef long Align;
union header 
{
    struct
    {
        union header *next;
        unsigned int size;
    }s;
    Align x;
};

typedef union header Header;

#define NALLOC 10

static Header *morecore(unsigned int nu);
void *Malloc(unsigned int nbytes);
void Free(void *ap);
void printlist(void);

#endif