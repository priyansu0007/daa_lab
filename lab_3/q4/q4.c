#include <stdio.h>
#include <stdlib.h>

// Function to find the next power of 2
int nextPowerOf2(int n) {
    int p = 1;
    while (p < n) {
        p *= 2;
    }
    return p;
}

// Function to allocate memory for an n x n matrix (initialized to 0)
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

// Function to add two matrices
void add(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Function to subtract two matrices
void sub(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Strassen's Algorithm
void strassen(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;

    int **A11 = allocateMatrix(newSize), **A12 = allocateMatrix(newSize);
    int **A21 = allocateMatrix(newSize), **A22 = allocateMatrix(newSize);
    int **B11 = allocateMatrix(newSize), **B12 = allocateMatrix(newSize);
    int **B21 = allocateMatrix(newSize), **B22 = allocateMatrix(newSize);
    
    int **C11 = allocateMatrix(newSize), **C12 = allocateMatrix(newSize);
    int **C21 = allocateMatrix(newSize), **C22 = allocateMatrix(newSize);

    int **M1 = allocateMatrix(newSize), **M2 = allocateMatrix(newSize);
    int **M3 = allocateMatrix(newSize), **M4 = allocateMatrix(newSize);
    int **M5 = allocateMatrix(newSize), **M6 = allocateMatrix(newSize);
    int **M7 = allocateMatrix(newSize);
    
    int **tempA = allocateMatrix(newSize), **tempB = allocateMatrix(newSize);

    // Divide matrices into 4 sub-matrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // M1 = (A11 + A22) * (B11 + B22)
    add(A11, A22, tempA, newSize);
    add(B11, B22, tempB, newSize);
    strassen(tempA, tempB, M1, newSize);

    // M2 = (A21 + A22) * B11
    add(A21, A22, tempA, newSize);
    strassen(tempA, B11, M2, newSize);

    // M3 = A11 * (B12 - B22)
    sub(B12, B22, tempB, newSize);
    strassen(A11, tempB, M3, newSize);

    // M4 = A22 * (B21 - B11)
    sub(B21, B11, tempB, newSize);
    strassen(A22, tempB, M4, newSize);

    // M5 = (A11 + A12) * B22
    add(A11, A12, tempA, newSize);
    strassen(tempA, B22, M5, newSize);

    // M6 = (A21 - A11) * (B11 + B12)
    sub(A21, A11, tempA, newSize);
    add(B11, B12, tempB, newSize);
    strassen(tempA, tempB, M6, newSize);

    // M7 = (A12 - A22) * (B21 + B22)
    sub(A12, A22, tempA, newSize);
    add(B21, B22, tempB, newSize);
    strassen(tempA, tempB, M7, newSize);

    // C11 = M1 + M4 - M5 + M7
    add(M1, M4, tempA, newSize);
    sub(tempA, M5, tempB, newSize);
    add(tempB, M7, C11, newSize);

    // C12 = M3 + M5
    add(M3, M5, C12, newSize);

    // C21 = M2 + M4
    add(M2, M4, C21, newSize);

    // C22 = M1 - M2 + M3 + M6
    sub(M1, M2, tempA, newSize);
    add(tempA, M3, tempB, newSize);
    add(tempB, M6, C22, newSize);

    // Combine results into final matrix C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    // Free memory
    freeMatrix(A11, newSize); freeMatrix(A12, newSize);
    freeMatrix(A21, newSize); freeMatrix(A22, newSize);
    freeMatrix(B11, newSize); freeMatrix(B12, newSize);
    freeMatrix(B21, newSize); freeMatrix(B22, newSize);
    freeMatrix(C11, newSize); freeMatrix(C12, newSize);
    freeMatrix(C21, newSize); freeMatrix(C22, newSize);
    freeMatrix(M1, newSize); freeMatrix(M2, newSize);
    freeMatrix(M3, newSize); freeMatrix(M4, newSize);
    freeMatrix(M5, newSize); freeMatrix(M6, newSize);
    freeMatrix(M7, newSize); freeMatrix(tempA, newSize);
    freeMatrix(tempB, newSize);
}

// Function to print a matrix up to size n
void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    
    printf("Enter the size of the square matrix (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Size must be a positive integer.\n");
        return 1;
    }

    // Calculate padded size (next power of 2)
    int m = nextPowerOf2(n);

    // Allocate memory using m to ensure matrices are a power of 2
    // calloc sets unused padded elements to 0 automatically
    int** A = allocateMatrix(m);
    int** B = allocateMatrix(m);
    int** C = allocateMatrix(m);

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

    // Perform Strassen's algorithm on the padded matrices of size m
    strassen(A, B, C, m);

    printf("\nResultant Matrix C (A * B):\n");
    // Print only the original n x n portion
    printMatrix(C, n);

    // Free the dynamically allocated memory of size m
    freeMatrix(A, m);
    freeMatrix(B, m);
    freeMatrix(C, m);

    return 0;
}