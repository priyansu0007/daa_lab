#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Utility function to print a matrix
void printMatrix(int n, int mat[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

// Function to get cofactor matrix for determinant calculation
void getCofactor(int n, int mat[n][n], int temp[n][n], int p, int q, int current_n) {
    int i = 0, j = 0;
    for (int row = 0; row < current_n; row++) {
        for (int col = 0; col < current_n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = mat[row][col];
                if (j == current_n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

// Recursive function to calculate the determinant
int determinant(int n, int mat[n][n], int current_n) {
    int D = 0; 
    if (current_n == 1) return mat[0][0];

    int temp[n][n]; 
    int sign = 1;   

    for (int f = 0; f < current_n; f++) {
        getCofactor(n, mat, temp, 0, f, current_n);
        D += sign * mat[0][f] * determinant(n, temp, current_n - 1);
        sign = -sign;
    }
    return D;
}

// Function to calculate the dominant Eigenvalue and Eigenvector using Power Iteration
void calculateEigen(int n, int mat[n][n]) {
    double x[n], x_new[n];
    double lambda = 0.0, lambda_old;
    double tolerance = 0.00001;
    int max_iter = 1000, step = 0;

    // Initialize the guess vector to 1.0
    for (int i = 0; i < n; i++) x[i] = 1.0;

    do {
        lambda_old = lambda;

        // Multiply: x_new = A * x
        for (int i = 0; i < n; i++) {
            x_new[i] = 0.0;
            for (int j = 0; j < n; j++) {
                x_new[i] += mat[i][j] * x[j];
            }
        }

        // Find the dominant element to approximate lambda
        lambda = x_new[0];
        for (int i = 1; i < n; i++) {
            if (fabs(x_new[i]) > fabs(lambda)) {
                lambda = x_new[i];
            }
        }

        if (lambda == 0.0) break; // Avoid division by zero

        // Normalize the vector
        for (int i = 0; i < n; i++) {
            x[i] = x_new[i] / lambda;
        }

        step++;
    } while (fabs(lambda - lambda_old) > tolerance && step < max_iter);

    printf("\n(vii) Dominant Eigenvalue: %.4f\n", lambda);
    printf("      Corresponding Eigenvector: [ ");
    for (int i = 0; i < n; i++) {
        printf("%.4f ", x[i]);
    }
    printf("]\n");
}


int main() {
    int n;
    printf("Enter the size (n) for the n x n square matrices: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid matrix size.\n");
        return 0;
    }

    int A[n][n], B[n][n], C[n][n];

    printf("\n--- Input Matrix A ---\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%d", &A[i][j]);
        }
    }

    printf("\n--- Input Matrix B (for Addition/Multiplication) ---\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("B[%d][%d]: ", i, j);
            scanf("%d", &B[i][j]);
        }
    }

    // (i) Matrix Addition: O(n^2)
    printf("\n(i) Matrix Addition (A + B):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    printMatrix(n, C);

    // (ii) Matrix Multiplication: O(n^3)
    printf("\n(ii) Matrix Multiplication (A * B):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    printMatrix(n, C);

    // (iii) Finding if A is a zero matrix: O(n^2)
    bool isZero = true;
    for (int i = 0; i < n && isZero; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] != 0) {
                isZero = false;
                break;
            }
        }
    }
    printf("\n(iii) Matrix A is %s Zero Matrix.\n", isZero ? "a" : "NOT a");

    // (iv) Finding if A is a symmetric matrix: O(n^2)
    bool isSymmetric = true;
    for (int i = 0; i < n && isSymmetric; i++) {
        for (int j = 0; j < i; j++) {
            if (A[i][j] != A[j][i]) {
                isSymmetric = false;
                break;
            }
        }
    }
    printf("(iv) Matrix A is %s Symmetric Matrix.\n", isSymmetric ? "a" : "NOT a");

    // (v) Computing the determinant of Matrix A: O(n!)
    int det = determinant(n, A, n);
    printf("(v) Determinant of Matrix A: %d\n", det);

    // (vii) Finding the Eigenvalue and Eigenvector: O(k * n^2) where k is iterations
    calculateEigen(n, A);

    // (vi) Transposing Matrix A in situ (in place): O(n^2)
    printf("\n(vi) Matrix A Transposed (In Situ):\n");
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
    printMatrix(n, A);

    return 0;
}