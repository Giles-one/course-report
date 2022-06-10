// gcc exp4_1.c -g && ./a.out < input4_1.txt
#include <stdio.h>
#include <stdlib.h>

/*
将会议开始时间和结束时间都排序，
这时候会议的开始时间和结束时间都是升序的。
遍历会议的开始时间，如果有会议i的开始时间小于某会议j的结束时间，
那么该会议i一定是需要开辟一个新会场的，而当会议i开始时间大于某会议j的结束时间，
该会议i可以利用之前的会场，而不需要开辟新的会场
*/
#define N 300
int s[N];
int f[N];

static int cmp(int *a, int *b) {
    return *a-*b;
}
int main() {
    int n, res;
    scanf("%d", &n);
    for (int i=0; i<n; i++) {
        scanf("%d%d", &s[i], &f[i]);
    }
    qsort(s, n, sizeof(int), (void*)cmp);
    qsort(f, n, sizeof(int), (void*)cmp);
    res = 0;
    for (int i=0, j=0; i<n; i++) {
        if (s[i]<f[j])
            res++;
        else
            j++;
    }
    printf("%d \n", res);
}