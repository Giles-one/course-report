// gcc IntegerFactor.c && ./a.out
/*
f(12) = f(2)*6 + f(3)*4 + f(4)*3 + f(6)*2 + f(12)*1
*/
#include <stdio.h>
void f(int n, int *cnt) {
    if(n==1) (*cnt)++;
    for(int i=2; i<=n; i++) {
        if(n%i == 0)
            f(n/i, cnt);
    }
}
int main() {
    int cnt=0;
    f(12, &cnt);
    printf("%d\n", cnt);
}
