#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI 3.14159265358979323846

// Recursive Fast Fourier Transform (FFT) / Inverse FFT
void fft(double complex *a, int n, int invert) {
    if (n <= 1) return;

    // Divide phase: separate into even and odd indices
    double complex *a0 = malloc(n / 2 * sizeof(double complex));
    double complex *a1 = malloc(n / 2 * sizeof(double complex));
    for (int i = 0; i < n / 2; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }

    // Conquer phase: recursive calls
    fft(a0, n / 2, invert);
    fft(a1, n / 2, invert);

    // Combine phase
    double angle = 2 * PI / n * (invert ? -1 : 1);
    double complex w = 1;
    double complex wn = cos(angle) + I * sin(angle);

    for (int i = 0; i < n / 2; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        w *= wn;
    }

    free(a0);
    free(a1);
}

// Function to find the next power of 2 greater than or equal to a number
int nextPowerOf2(int val) {
    int p = 1;
    while (p < val) {
        p *= 2;
    }
    return p;
}

int main() {
    int m, n;
    printf("Enter the size of vector A (m) and vector B (n) [Note: n >= m]: ");
    scanf("%d %d", &m, &n);

    if (m > n) {
        printf("Condition n >= m not met.\n");
        return 0;
    }

    int result_len = m + n - 1;
    int L = nextPowerOf2(result_len);

    // Allocate padded arrays initialized to 0
    double complex *A = calloc(L, sizeof(double complex));
    double complex *B = calloc(L, sizeof(double complex));

    printf("Enter %d elements for vector A:\n", m);
    for (int i = 0; i < m; i++) {
        double val;
        scanf("%lf", &val);
        A[i] = val + 0 * I;
    }

    printf("Enter %d elements for vector B:\n", n);
    for (int i = 0; i < n; i++) {
        double val;
        scanf("%lf", &val);
        B[i] = val + 0 * I;
    }

    // 1. Compute FFT of A and B
    fft(A, L, 0);
    fft(B, L, 0);

    // 2. Point-wise multiplication
    double complex *C = calloc(L, sizeof(double complex));
    for (int i = 0; i < L; i++) {
        C[i] = A[i] * B[i];
    }

    // 3. Compute Inverse FFT
    fft(C, L, 1);

    // The result needs to be divided by L due to the IFFT formula scaling
    for (int i = 0; i < L; i++) {
        C[i] /= L;
    }

    // Print the final Convolution Vector
    printf("\nConvolution Vector C (first %d elements):\n", result_len);
    for (int i = 0; i < result_len; i++) {
        // We round the real part to handle minor floating-point inaccuracies
        printf("%.0f ", round(creal(C[i]))); 
    }
    printf("\n");

    free(A);
    free(B);
    free(C);

    return 0;
}