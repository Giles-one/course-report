//gcc exp3_2_2.c -g && ./a.out 
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
            // printf("%2d ", b[i][j]);
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

int LCSRec(int i, int j, char* x, char* y) {
    int ret;
    if (i==0 || j==0) {
        b[i][j] == 0;
        return 0;
    } 
    if (x[i-1] == y[j-1]) {
        ret = LCSRec(i-1, j-1, x, y) + 1;
        b[i][j] = RD;
    } else {
        
        int u = LCSRec(i-1, j, x, y);
        int l = LCSRec(i, j-1, x, y);
        if (u >= l) {
            ret = u;
            b[i][j] = D;
        } else {
            ret = l;
            b[i][j] = R;
        }
    }
    return ret;
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
    LCSRec(m, n, x, y);
    display(m, n, x, y);
    trace(m, n, x);
    printf("\n");
    return 0;
}