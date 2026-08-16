#include <stdio.h>
#include <stdlib.h>

// Function to check if a number is a power of 2
int isPowerOfTwo(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

// Function to allocate memory for an n x n matrix
int** allocateMatrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)calloc(n, sizeof(int));
    }
    return matrix;
}

// Function to free allocated memory
void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to print a matrix
void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// O(n^2) Divide and Conquer Multiplication for the special structured matrices
void specialMultiply(int** A, int** B, int** C, int n) {
    // Base Case: 1x1 matrix
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int half = n / 2;

    // Allocate intermediate matrices of size (n/2) x (n/2)
    int **SA = allocateMatrix(half); // A1 + A2
    int **SB = allocateMatrix(half); // B1 + B2
    int **DA = allocateMatrix(half); // A1 - A2
    int **DB = allocateMatrix(half); // B1 - B2
    int **X  = allocateMatrix(half); // (A1 + A2) * (B1 + B2)
    int **Y  = allocateMatrix(half); // (A1 - A2) * (B1 - B2)

    // Construct SA, SB, DA, DB in O(n^2) time
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int a1 = A[i][j];             // Top-Left block
            int a2 = A[i][j + half];      // Top-Right block
            
            int b1 = B[i][j];             // Top-Left block
            int b2 = B[i][j + half];      // Top-Right block

            SA[i][j] = a1 + a2;
            DA[i][j] = a1 - a2;

            SB[i][j] = b1 + b2;
            DB[i][j] = b1 - b2;
        }
    }

    // Recursive Calls (Only 2 multiplications instead of 4 or 8)
    specialMultiply(SA, SB, X, half);
    specialMultiply(DA, DB, Y, half);

    // Combine results into final matrix C in O(n^2) time
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            // C1 = (X + Y) / 2
            int c1 = (X[i][j] + Y[i][j]) / 2;
            
            // C2 = (X - Y) / 2
            int c2 = (X[i][j] - Y[i][j]) / 2;

            // Place C1 on main diagonal blocks
            C[i][j] = c1;                       // Top-Left
            C[i + half][j + half] = c1;         // Bottom-Right

            // Place C2 on off-diagonal blocks
            C[i][j + half] = c2;                // Top-Right
            C[i + half][j] = c2;                // Bottom-Left
        }
    }

    // Free intermediate memory
    freeMatrix(SA, half); freeMatrix(SB, half);
    freeMatrix(DA, half); freeMatrix(DB, half);
    freeMatrix(X, half);  freeMatrix(Y, half);
}

int main() {
    int n;

    printf("Enter the size of the matrix n (must be a power of 2, e.g., 2, 4, 8): ");
    if (scanf("%d", &n) != 1 || !isPowerOfTwo(n)) {
        printf("Invalid input. Size must be a positive integer power of 2.\n");
        return 1;
    }
    
    int** A = allocateMatrix(n);
    int** B = allocateMatrix(n);
    int** C = allocateMatrix(n);

    printf("\nNote: Please ensure the inputted matrices follow the special recursive block pattern.\n");
    
    printf("\nEnter the elements of Matrix A (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("\nEnter the elements of Matrix B (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    // Print the inputs to verify
    printf("\nMatrix A:\n");
    printMatrix(A, n);

    printf("\nMatrix B:\n");
    printMatrix(B, n);

    // Call the O(n^2) algorithm
    specialMultiply(A, B, C, n);

    printf("\nResultant Matrix C (A * B):\n");
    printMatrix(C, n);

    // Free dynamically allocated matrices
    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}