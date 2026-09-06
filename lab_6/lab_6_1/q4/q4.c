#include <stdio.h>
#include <limits.h>

#define MAX 100

void printOptimalParenthesis(int s[MAX][MAX], int i, int j, char *name) {
    if (i == j) {
        printf("%c%d", *name, i);
        return;
    }
    printf("(");
    printOptimalParenthesis(s, i, s[i][j], name);
    printOptimalParenthesis(s, s[i][j] + 1, j, name);
    printf(")");
}

void matrixChainOrder(int p[], int n) {
    int m[MAX][MAX];
    int s[MAX][MAX];

    for (int i = 1; i < n; i++) {
        m[i][i] = 0;
    }

    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("Minimum number of scalar multiplications: %d\n", m[1][n - 1]);
    
    char matrixName = 'A';
    printf("Optimal Parenthesization: ");
    printOptimalParenthesis(s, 1, n - 1, &matrixName);
    printf("\n");

    printf("\n--- Cost Matrix (m) ---\n");
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i <= j)
                printf("%6d ", m[i][j]);
            else
                printf("%6s ", "-");
        }
        printf("\n");
    }

    printf("\n--- Split/Parenthesis Matrix (s) ---\n");
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i < j)
                printf("%4d ", s[i][j]);
            else
                printf("%4s ", "-");
        }
        printf("\n");
    }
}

int main() {
    int p[] = {40, 20, 30, 10, 30};
    int n = sizeof(p) / sizeof(p[0]);

    printf("Matrix Dimensions:\n");
    for (int i = 1; i < n; i++) {
        printf("A%d: %d x %d\n", i, p[i - 1], p[i]);
    }
    printf("\n");

    matrixChainOrder(p, n);

    return 0;
}