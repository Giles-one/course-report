//gcc exp3_2_3.c -g && ./a.out 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true  1
#define false 0

#define RD 1 /* right down */
#define R  2 /* right */
#define D  3 /* down */

#define N 30
int c[N][N];
int b[N][N];
int is_written[N][N];

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

int LCSLength(int i, int j, char* x, char* y) {
    if (is_written[i][j] == 1) 
        return c[i][j];
    
    if (i==0 || j==0) {
        c[i][j] = 0;
        is_written[i][j] = true;
        return 0;
    }
    if (x[i-1] == y[j-1]) {
        c[i][j] = LCSLength(i-1, j-1, x, y) + 1;
        b[i][j] = RD;
        is_written[i][j] = true;
    } else {
        int u = LCSLength(i-1, j, x, y);
        int l = LCSLength(i, j-1, x, y);
        if (u >= l) {
            c[i][j] = u;
            b[i][j] = D;
            is_written[i][j] = true;
        } else {
            c[i][j] = l;
            b[i][j] = R;
            is_written[i][j] = true;
        }
    }
    return c[i][j];

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

struct {
    char* buf;
    int size;
} obj;

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