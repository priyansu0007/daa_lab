#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Utility function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Compare function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid array size.\n");
        return 0;
    }

    int arr[n];
    int sorted_arr[n]; // Copy used for sorting-dependent operations
    
    printf("Enter %d unsorted integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sorted_arr[i] = arr[i]; // Store a copy
    }

    // (i) & (ii) First and second largest elements
    int first_max = arr[0], second_max = -2147483648; 
    for (int i = 1; i < n; i++) {
        if (arr[i] > first_max) {
            second_max = first_max;
            first_max = arr[i];
        } else if (arr[i] > second_max && arr[i] != first_max) {
            second_max = arr[i];
        }
    }
    
    printf("\n--- Results ---\n");
    printf("(i) Maximum element: %d\n", first_max);
    if (n > 1) {
        printf("(ii) First largest: %d, Second largest: %d\n", first_max, second_max);
    }

    // (iii) Mean
    double sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    double mean = sum / n;
    printf("(iii) Mean: %.2f\n", mean);

    // (v) Standard Deviation
    double variance_sum = 0;
    for (int i = 0; i < n; i++) {
        variance_sum += pow(arr[i] - mean, 2);
    }
    double std_dev = sqrt(variance_sum / n);
    printf("(v) Standard Deviation: %.2f\n", std_dev);

    // Sort the copied array for median, mode, and duplicate logic
    qsort(sorted_arr, n, sizeof(int), compare);

    // (iv) Median 
    double median;
    if (n % 2 == 0) {
        median = (sorted_arr[n/2 - 1] + sorted_arr[n/2]) / 2.0;
    } else {
        median = sorted_arr[n/2];
    }
    printf("(iv) Median: %.2f\n", median);

    // (vi) Mode
    int mode = sorted_arr[0], max_count = 1, current_count = 1;
    for (int i = 1; i < n; i++) {
        if (sorted_arr[i] == sorted_arr[i-1]) {
            current_count++;
        } else {
            current_count = 1;
        }
        if (current_count > max_count) {
            max_count = current_count;
            mode = sorted_arr[i];
        }
    }
    printf("(vi) Mode: %d (appears %d times)\n", mode, max_count);

    // (vii) Removing all duplicates 
    printf("(vii) Array without duplicates: ");
    printf("%d ", sorted_arr[0]);
    for (int i = 1; i < n; i++) {
        if (sorted_arr[i] != sorted_arr[i-1]) {
            printf("%d ", sorted_arr[i]);
        }
    }
    printf("\n");

    // (viii) Reversing the elements 
    printf("(viii) Reversed original array: ");
    for (int i = 0; i < n / 2; i++) {
        swap(&arr[i], &arr[n - 1 - i]);
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Revert the array back to original for partitioning
    for (int i = 0; i < n / 2; i++) swap(&arr[i], &arr[n - 1 - i]);

    // (ix) Partitioning the array
    int pivot;
    printf("\n(ix) Enter a pivot element for partitioning: ");
    scanf("%d", &pivot);
    
    int partition_index = -1;
    for (int j = 0; j < n; j++) {
        if (arr[j] < pivot) {
            partition_index++;
            swap(&arr[partition_index], &arr[j]);
        }
    }
    
    printf("Partitioned array (< %d on left, >= %d on right): ", pivot, pivot);
    for (int k = 0; k < n; k++) {
        printf("%d ", arr[k]);
    }
    printf("\n");

    return 0;
}