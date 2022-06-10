// gcc SetPart1.c && ./a.out
/*
f(n, m) // n个数分成，m个集合
对于任意一个元素来说，
1. 自己做一个集合，剩余的n-1交给子任务. f(n-1, m-1)
2. 自己不做一个集合，加入到某个集合中，子任务 f(n-1, m). 则有m个集合任自己加入，就是m*f(n-1. m)

Normal case:
	f(n, m) = f(n-1. m-1) + f(n-1, m)*m

Base case:
	对于f(n, m)
	* 子问题 f(n-1. m-1)说明 arg1, arg2在减小
	n==1 || m==1 return 1

	* 子问题 f(n-1, m)  说明 arg2/arg1 在增大
	n==m return 1

综上:
	f(n, m) = f(n-1, m-1) + f(n-1, m)*m
	F(n) = f(n, 1) + f(n, 2) + .... + f(n, n)
*/

#include<stdio.h>
int f(int n, int m) {
	if(n==m) return 1;
	if(n==1 || m==1) return 1;

	return f(n-1, m-1) + f(n-1, m)*m;
}
int F(int n) {
	int cnt = 0;
	for (int m=1; m<=n; m++) {
		cnt += f(n, m);
	}
	return cnt;
}
int main() {
	printf("%d\n", F(6));
}
