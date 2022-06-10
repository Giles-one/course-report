#include <stdio.h>
#include "my_malloc.h"

int main() {
    char *p[200],*str;
    int i;
    printf("sizeof(Header)%ld\n\n", sizeof(Header));

    for(i=0;i<5;i++) {
        p[i]=(char*)Malloc(8);
        printf("\nMalloc %d,%p\n",i,p[i]);
    }
    
    printf("========================\n=======================\n");
    if((str = (char*)Malloc(8))==NULL) {
        printf("Malloc str error\n");
        exit(1);
    }
    
    for(i=2;i>=1;i--) {
        Free(p[i]);
        printf("\nfree %d,%p\n",i,p[i]);
    }
    printlist();
    
    for(i=0;i<5;i++) {
        p[i]=(char*)Malloc(8);
        printf("\nMalloc %d,%p\n",i,p[i]);
    }
    printlist();
    return 0;
}
