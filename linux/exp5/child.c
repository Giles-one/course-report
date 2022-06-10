#include <stdio.h>
int main () {
    int i, j;
    for (int i=0; i<1000000; i++)
        for(j=0; j<1000; j++);
    printf("after 1,000,000,000 loops\n");
    return 0;
}