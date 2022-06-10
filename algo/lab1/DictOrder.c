// gcc DictOrder.c && ./a.out
#include <stdio.h>
#include <stdlib.h>

int fac(int n) {
    int ret = 1;
    for(int i=1; i<=n; i++) {
        ret *= i;
    }
    return ret;
}
int order(int a[], int n) {
    int ret = 0;
    for (int i=1; i<a[n]; i++) {
        ret++;
        for(int k=0; k<n; k++) {
            if(a[k] == i) {
                ret--;
                break;
            }
        }
    }
    return ret;
}
int DictOrder(int a[], int p, int q) {
    if (p==q-1) return 1;
    int cnt = 0;
    cnt = DictOrder(a, p+1, q);
    cnt += order(a, p)*fac(q-p);
    return cnt;
}

int main() {
    int order;
    
    char A[8] = "26458173";
    int *data = malloc(8*sizeof(int));
    for (int i=0; i<8; i++)
        data[i] = A[i] - '0';   
    order = DictOrder(data, 0, 7);
    printf("%d \n", order);
}