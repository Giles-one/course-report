// gcc SetPart2.c && ./a.out
#include<stdio.h>
int f(int n, int m) {
    /* f**king case */
    if(m>n) return 0; 
    /* base case */
    if(n==m) return 1;
	if(n==1 || m==1) return 1;
    /* normal case */
	return f(n-1, m-1) + f(n-1, m)*m;
}
int main() {
    printf("%d\n", f(6, 2));
    return 0;
}
