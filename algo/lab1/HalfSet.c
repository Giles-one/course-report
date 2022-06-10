// gcc HalfSet.c -g && echo "6" | ./a.out
#include <stdio.h>

int HalfSet(int n) {
    int ret = 1;
    for(int i=1; i<=n/2; i++) {
        ret += HalfSet(i);
    }
    return ret;
 }

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", HalfSet(n));
}