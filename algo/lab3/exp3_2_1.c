//gcc exp3_2_3.c -g && ./a.out 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RD 1 /* right down */
#define R  2 /* right */
#define D  3 /* down */

#define N 30
int c[N][N];
int b[N][N];

void display(int m, int n, char* x, char* y) {
    printf(" \\  0 ");
    for(int i=0; i<=m; i++)
        printf(" %c ", y[i]);
    printf("\n");
    for(int i=0; i<=m; i++) {
        if (i==0)
            printf("0 |");
        else
            printf("%c |", x[i-1]);
        for (int j=0; j<=n; j++) {
            // printf("%2d ", c[i][j]);
            switch(b[i][j]) {
                case 0    : printf(" 0 "); break;
                case RD   : printf(" ↖ "); break;
                case R    : printf(" ← "); break;
                case D    : printf(" ↑ "); break;
            }
        }
        printf("\n");
        fflush(stdout);
    }
}

void LCSLength(int m, int n, char* x, char* y) {
    for (int i=0; i<=m; i++)
        c[0][i] = 0;
    for (int i=0; i<=n; i++)
        c[i][0] = 0;
    for (int i=1; i<=m; i++) {
        for (int j=1; j<=n; j++) {
            /* take care of x's and y's index*/
            if(x[i-1] == y[j-1]) {
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = RD;
            } else if (c[i-1][j] >= c[i][j-1]) {
                c[i][j] = c[i-1][j];
                b[i][j] = D;
            } else {
                c[i][j] = c[i][j-1];
                b[i][j] = R;
            }
        }
    }
}

void trace(int i, int j, char* x) {
    if (i==0 || j==0) 
        return;
    if (b[i][j] == RD) {
        trace(i-1, j-1, x);
        printf("%c", x[i-1]);
    } else if (b[i][j] == D) {
        trace(i-1, j, x);
    } else {
        trace(i, j-1, x);
    }
}

int main() {
    char* x = "ABCBDAB";
    char* y = "BDCABA";
    int m = strlen(x);
    int n = strlen(y);
    LCSLength(m, n, x, y);
    display(m, n, x, y);
    trace(m, n, x);
    printf("\n");
    return 0;
}