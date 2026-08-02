#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// (i) Bubble sort that terminates if the array is sorted before the (n-1)th pass.
long long bubbleSortOptimized(int arr[], int n) {
    long long comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0) {
            break; // Terminates early
        }
    }
    return comparisons;
}

// (ii) Bubble sort that always completes the (n-1)th pass.
long long bubbleSortUnoptimized(int arr[], int n) {
    long long comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return comparisons;
}

// Generates a "Nearly Sorted" Randomized Sequence
// It creates a sorted sequence, then applies a few random swaps.
// This perfectly highlights the early-termination efficiency.
void generateNearlySortedRandom(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i; 
    }
    
    // Perform exactly 5 completely random swaps
    for (int i = 0; i < 5; i++) {
        int idx1 = rand() % n;
        int idx2 = rand() % n;
        int temp = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = temp;
    }
}

// Helper to copy the array so both algorithms sort the exact same data
void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

int main() {
    FILE *fp = fopen("bubble_data.dat", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    srand(time(NULL));
    int max_n = 2000;
    int step = 100;

    fprintf(fp, "# N Unoptimized_Comps Optimized_Comps\n");

    for (int n = step; n <= max_n; n += step) {
        int *original = (int *)malloc(n * sizeof(int));
        int *test1 = (int *)malloc(n * sizeof(int));
        int *test2 = (int *)malloc(n * sizeof(int));

        generateNearlySortedRandom(original, n);
        
        copyArray(original, test1, n);
        copyArray(original, test2, n);

        long long comp_unopt = bubbleSortUnoptimized(test1, n);
        long long comp_opt = bubbleSortOptimized(test2, n);

        fprintf(fp, "%d %lld %lld\n", n, comp_unopt, comp_opt);

        free(original);
        free(test1);
        free(test2);
    }

    fclose(fp);
    printf("Data generated and saved to 'bubble_data.dat'.\n");
    return 0;
}