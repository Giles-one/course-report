// gcc integerPart.c -g && ./a.out
#include <stdio.h>

int intPart(int n, int m) {
    if (n<1 || m<1)
        return 0;
    if (n==1 || m==1) 
        return 1;
    if (m > n)
        return intPart(n, n);
    if (m == n)
        return 1 + intPart(n, m-1);
    return intPart(n, m-1) + intPart(n-m, m);
}

int main() {
    printf("%d\n", intPart(6, 2));
}