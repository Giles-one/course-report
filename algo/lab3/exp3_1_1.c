// gcc exp3_1_1.c && ./a.out 
#include <stdio.h>
#include <stdlib.h>

#define MAX 0x3ffff
#define N 30
int s[N][N];
int m[N][N];
/*
void matrixMultiply(int (*a)[100], int (*b)[100], int (*c)[100], int ra, int ca, int rb, int cb) {
    if (ca != rb) {
        perror("ca != rb");
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<ra; i++) {
        for (int j=0; j<cb; j++) {
            int sum = a[i][0] * b[0][i]
            for(int k=1; k<ca; k++) {
                sum += a[i][k]*b[k][j]
            }
            c[i][j] = sum;
        }
    }
}
*/
void dispaly(int n) {
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            printf("%5d ", m[i][j]);
        }
        printf("\n");
        fflush(stdout);
    }
}

void PrintSolution(int i, int j) {
    if (i==j) {
        printf("A%d", i);
    } else {
        printf("(");
        PrintSolution(i, s[i][j]);
        PrintSolution(s[i][j]+1, j);
        printf(")");
    }
}

/* brute force */
void MatrixChain(int n, int* p) {
    for (int i=1; i<=n; i++) {
        m[i][i] = 0;
    }
    for (int l=2; l<=n; l++) {
        for (int i=1; i<=n-l+1; i++) {
            int j = i+l-1;
            m[i][j] = MAX;
            for (int k=i; k<=j-1; k++) {
                int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q<m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}
int main() {
    int p[] = {30, 35, 15, 5, 10, 20, 25};
    int n = sizeof(p)/sizeof(int)-1;
    MatrixChain(n, p);
    PrintSolution(1, n);
    printf("\n");
}
