#include <stdio.h>
#include <math.h>

int main() {
    FILE *fp = fopen("data_loglog.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "# log10(n) log10(1/n) log10(log2(n)) log10(12*sqrt(n)) ...\n");

    // We can now safely test massive values of n!
    // Using exponential growth for the loop to space out data points evenly on a log axis
    for (double n = 20; n <= 10000000; n *= 2) {
        
        double log_n = log10(n);
        
        // Math rules: log10(a * b) = log10(a) + log10(b)
        // log10(a^b) = b * log10(a)
        
        double f1 = -log_n;                                   // log10(1/n)
        double f2 = log10(log2(n));                           // log10(log2(n))
        double f3 = log10(12.0) + 0.5 * log_n;                // log10(12 * n^0.5)
        double f4 = log10(50.0) + 0.5 * log_n;                // log10(50 * n^0.5)
        double f5 = 0.51 * log_n;                             // log10(n^0.51)
        double f6 = (32.0 * log10(2.0)) + log_n;              // log10(2^32 * n)
        double f7 = log_n + log10(log2(n));                   // log10(n * log2(n))
        double f8 = log10(n * n - 324.0);                     // log10(n^2 - 324)
        double f9 = log10(100.0 * n * n + 6.0 * n);           // log10(100n^2 + 6n)
        double f10 = log10(2.0) + 3.0 * log_n;                // log10(2 * n^3)
        double f11 = log2(n) * log_n;                         // log10(n^log2(n))
        double f12 = n * log10(3.0);                          // log10(3^n) - Avoids overflow!

        fprintf(fp, "%.4f %e %e %e %e %e %e %e %e %e %e %e %e\n",
               log_n, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12);
    }

    fclose(fp);
    printf("Logarithmic data generated successfully!\n");
    return 0;
}