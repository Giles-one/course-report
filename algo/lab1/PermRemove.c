// gcc exp1_4.c -g && ./a.out
#include <stdio.h>
#define swap(a, b) do { typeof(a) t; t=a; a=b; b=t; } while(0) 

void printArray(char str[], int n) {
    for (int i=0; i<n; i++) {
        printf("%c ", str[i]);
    }
    printf("\n");
}
void perm(char A[], int p, int q) {
    if (p == q) {
        printArray(A, q+1);
        return;
    }
    int k;
    for (int i=p; i<=q; i++) {
        for (k=p; A[i]!=A[k] ;k++);
        if(k != i)  continue;
    /* A[p] ...p[i-1] != A[i] */
        swap(A[p], A[i]);
        perm(A, p+1, q);
        swap(A[p], A[i]);
    }
}

int main() {
    char A[] = "ccaa";
    perm(A, 0, 3);
}