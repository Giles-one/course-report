// gcc exp2_3.c && ./a.out
#include <stdio.h>
#include <stdlib.h>

int line;
int (*table)[0x100];

void display() {
    for (int i=1; i<=line; i++) {
        for (int j=1; j<=line; j++) {
            printf("%-3d ", table[i][j]);
        }
        printf("\n");
        fflush(stdout);
    }
}

void table_fill(int k) {
    int n = 1;
    for (int i=1; i<=k; i++)
        n *= 2;
    line = n;
    for (int i=1; i<=n; i++)
        table[1][i] = i;
    int m = 1;
    for (int s=1; s<=k; s++) {
        n /= 2;
        /* t, ☞向右走的方格数, 与m夹在两端 */
        for (int t=1; t<=n; t++) {
            /* i, j, 行列控制,不能大于2*m,即当前方格的边长 */
            for (int i=m+1; i<=2*m; i++) {
                for (int j=m+1; j<=2*m; j++) {
                    /* 写入方格的两角 */
                    table[i][j+(t-1)*m*2] = table[i-m][j+(t-1)*m*2-m];
                    table[i][j+(t-1)*m*2-m] = table[i-m][j+(t-1)*m*2];
                    // printf("i=%d j=%d t=%d m=%d t=%d s=%d \n", i, j, t, m, t, s);
                    // display();
                }
            }
        }
        m *= 2;
    }
}

int main() {
    table = malloc(sizeof(int)*0x100*0x100);
    table_fill(3);
    display();
    return 0;
}
