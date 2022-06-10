// gcc Modes.c -g && ./a.out < Modes_input.txt
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cmp(int *a, int *b) {
    return *a-*b;
}

int modecnt = 0;
int Mode(int a[], int i, int j) {
    if (i==j) return 1;

    int m = (i+j)/2;
    int l=i, r=j;
    
    while(a[l] != a[m]) l++;
    while(a[r] != a[m]) r--;

    int mode, ct;
    ct = r-l+1;
    if(ct > modecnt) {
        modecnt = ct;
        mode = a[m];
    }
    
    int ret;
    if (l-i > modecnt) {
        ct = modecnt;
        ret = Mode(a, i, l-1);
        if(ct != modecnt) {
            mode = ret;
        }
    }
    if (j-r > modecnt) {
        ct = modecnt;
        ret = Mode(a, r+1, j);
        if (ct != modecnt) {
            mode = ret;
        }
    }
    return mode;
}

int main() {
    
    int n;
    scanf("%d", &n);
    int *data = malloc(n * sizeof(int));
    for(int i=0; i<n; i++) {
        scanf("%d", &data[i]);
    }
    qsort(data, n, sizeof(int), (void*)cmp);
    printf("mode = %d \n", Mode(data, 0, n-1));
    printf("modecnt = %d \n", modecnt);
    return 0;
}
