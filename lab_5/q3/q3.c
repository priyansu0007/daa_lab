#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Partition function for Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choosing the last element as the pivot
    int i = (low - 1);     // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// The main Quick Sort recursive function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now at right place
        int pi = partition(arr, low, high);

        // Separately sort elements before partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int n;
    
    printf("Enter the number of elements to generate and sort: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    // 1. Generate random numbers and write them to a file
    FILE *fp_in = fopen("unsorted.txt", "w");
    if (fp_in == NULL) {
        printf("Error: Could not create 'unsorted.txt'.\n");
        return 1;
    }
    
    // Seed the random number generator
    srand(time(0)); 
    for (int i = 0; i < n; i++) {
        fprintf(fp_in, "%d\n", rand() % 10000); // Generates numbers from 0 to 9999
    }
    fclose(fp_in);
    printf("Successfully generated and wrote %d random numbers to 'unsorted.txt'.\n", n);

    // 2. Dynamically allocate memory to read the numbers back
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    // 3. Read the numbers from the file into the array
    fp_in = fopen("unsorted.txt", "r");
    if (fp_in == NULL) {
        printf("Error: Could not open 'unsorted.txt' for reading.\n");
        free(arr);
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        fscanf(fp_in, "%d", &arr[i]);
    }
    fclose(fp_in);

    // 4. Sort the array using Quick Sort
    quickSort(arr, 0, n - 1);
    printf("Array sorted successfully using Quick Sort in memory.\n");

    // 5. Write the sorted numbers to a new output file
    FILE *fp_out = fopen("sorted.txt", "w");
    if (fp_out == NULL) {
        printf("Error: Could not create 'sorted.txt'.\n");
        free(arr);
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        fprintf(fp_out, "%d\n", arr[i]);
    }
    fclose(fp_out);
    printf("Sorted numbers have been written to 'sorted.txt'.\n");

    // Free the dynamically allocated memory
    free(arr);

    return 0;
}