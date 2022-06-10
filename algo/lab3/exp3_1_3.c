// gcc exp3_1_3.c && ./a.out 
#include <stdio.h>
#include <stdlib.h>

#define MAX 0x3ffff
#define N 30
int s[N][N];
int m[N][N];

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

/* DP table */
int MatrixChainDP(int n, int *p) {
    for (int i=1; i<=n; i++) {
        m[i][i] = 0;
    }
    for (int r=2; r<=n; r++) {
        for (int i=1; i<=n-r+1; i++) {
            int j = i+r-1;
            m[i][j] = m[i+1][j] + p[i-1]*p[i]*p[j];
            s[i][j] = i;
            for (int k=i+1; k<j; k++) {
                int cost = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (cost<m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
}

int main() {
    int p[] = {30, 35, 15, 5, 10, 20, 25};
    int n = sizeof(p)/sizeof(int)-1;
    MatrixChainDP(n, p);
    PrintSolution(1, n);
    printf("\n");
}

/*
int MatrixChainRec(int (*m)[100], int i, int j, int *p) {
    if (i==j) {
        m[i][j] = 0;
        return m[i][j];
    } else {
        int cost;
        for (int k=i; k<j; k++) {
            cost = MatrixChainRec(m, i, k, p) + MatrixChainRec(m, k+1, j, p) + p[i-1]*p[k]*p[j];
            if (m[i][j] > cost)
                m[i][j] = cost;
        }
        return m[i][j];
    }
}
*/