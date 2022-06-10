// gcc exp4_9.c -g && ./a.out < input4_9.txt
#include <stdio.h>
#include <stdlib.h>

#define N 30
int x[N];

int main() {
    int n, k, cnt;
    scanf("%d%d", &n, &k);
    for (int i=0; i<k+1; i++)
        scanf("%d", &x[i]);
    cnt = 0;
    for (int i=0, s=0; i<k+1; i++) {
        s += x[i];
        if (s>n) { // 即将要行驶的路超过 一箱油所能跑的最远距离
            cnt++;
            s = x[i]; // reset s
        }
    }
    printf("cnt %d \n", cnt);
    return 0;
}