#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    int n;
    
    printf("Enter the number of elements to generate and sort: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    FILE *fp_in = fopen("unsorted.txt", "w");
    if (fp_in == NULL) {
        printf("Error: Could not create 'unsorted.txt'.\n");
        return 1;
    }
    
    srand(time(0)); 
    for (int i = 0; i < n; i++) {
        fprintf(fp_in, "%d\n", rand() % 10000);
    }
    fclose(fp_in);
    printf("Successfully generated and wrote %d random numbers to 'unsorted.txt'.\n", n);

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

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

    heapSort(arr, n);
    printf("Array sorted successfully using Heap Sort in memory.\n");

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

    free(arr);

    return 0;
}