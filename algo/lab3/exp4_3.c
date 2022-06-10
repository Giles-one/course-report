// gcc exp4_3.c -g && ./a.out < input4_3.txt 
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int l;
    int p;
}tap;
static int cmp(int* a, int* b) {
    return *a-*b;
}
int main() {
    float res;
    int n, all, time;

    scanf("%d", &n);
    tap *tap = malloc(sizeof(tap)*n);
    int* m = malloc(sizeof(int)*n);
    
    for (int i=0; i<n; i++) {
        scanf("%d%d",&tap[i].l, &tap[i].p);
    }

    all = 0;
    for (int i=0; i<n; i++) {
        all += tap[i].p;
        m[i] = tap[i].p*tap[i].l;
    }
    qsort(m, n, sizeof(int), (void*)cmp);
    
    time = 0;
    for (int i=0; i<n; i++)
        time += (n-i)*m[i];
    res = (float)time/all;
    printf("%.4f \n", res);
    return 0;
}