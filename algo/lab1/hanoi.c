// gcc hanoi.c && ./a.out
/*
n, now, target, tmp

f(n, now, target, other) =
    f(n-1, now, other, target) +
    mov(now, target) + 
    f(n-1, other, target, now)

*/
#include <stdio.h>

#define move(n, from, to) do{ printf("move %d from %c to %c \n", n, from, to); } while(0)
void hanoi(int n, char now, char target, char other) {
    if(n == 0)  return;

    hanoi(n-1, now, other, target);
    move(n, now, target);
    hanoi(n-1, other, target, now);
}

int main() {
    hanoi(3, 'A', 'B', 'C');
}

/*
数学归纳法证明，颜色问题
把颜色看成奇偶
hanoi(2, 'A', 'B', 'C');
move 1 from A to C 
move 2 from A to B 
move 1 from C to B 

hanoi(3, 'A', 'B', 'C') = hanoi(2, 'A', 'C', 'B') #1
                        + mov(3, 'A', 'B')        #2
                        + hanoi(2, 'C', 'B', 'A') #3

#1 是hanoi(2, 'A', 'B', 'C'), 重复颜色
#2 目标已经是排好序的，自然颜色不重复
#3 的第二部会把move 2 from C to B，2和3也不重复
*/
