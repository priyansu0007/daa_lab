#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Binary Search tracking total element comparisons
int binarySearch(int arr[], int size, int key, int *comparisons) {
    int l = 0, r = size - 1;
    *comparisons = 0;

    while (l <= r) {
        int mid = l + (r - l) / 2;

        (*comparisons)++; // Comparison 1: arr[mid] == key
        if (arr[mid] == key) return mid;

        (*comparisons)++; // Comparison 2: arr[mid] < key
        if (arr[mid] < key) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return -1;
}

// Ternary Search tracking total element comparisons
int ternarySearch(int arr[], int size, int key, int *comparisons) {
    int l = 0, r = size - 1;
    *comparisons = 0;

    while (r >= l) {
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;

        (*comparisons)++; // Comparison 1: arr[mid1] == key
        if (arr[mid1] == key) return mid1;

        (*comparisons)++; // Comparison 2: arr[mid2] == key
        if (arr[mid2] == key) return mid2;

        (*comparisons)++; // Comparison 3: key < arr[mid1]
        if (key < arr[mid1]) {
            r = mid1 - 1;
        } else {
            (*comparisons)++; // Comparison 4: key > arr[mid2]
            if (key > arr[mid2]) {
                l = mid2 + 1;
            } else {
                l = mid1 + 1;
                r = mid2 - 1;
            }
        }
    }
    return -1;
}

// Helper function to generate a random sorted array
void generateSortedArray(int arr[], int size) {
    arr[0] = rand() % 10;
    for (int i = 1; i < size; i++) {
        arr[i] = arr[i - 1] + (rand() % 5) + 1;
    }
}

int main() {
    srand(time(NULL));

    int size ;
    scanf("%d",&size);
    int *arr = (int *)malloc(sizeof(int) * size);

    generateSortedArray(arr, size);

    // Select a target element from the middle-to-end range for testing
    int targetIndex = (rand() % (size / 2)) + (size / 2);
    int key = arr[targetIndex];

    int comparisonsBinary = 0;
    int comparisonsTernary = 0;

    int indexBinary = binarySearch(arr, size, key, &comparisonsBinary);
    int indexTernary = ternarySearch(arr, size, key, &comparisonsTernary);

    printf("Array Size: %d\n", size);
    printf("Target Element: %d (Index %d)\n\n", key, targetIndex);

    printf("--- Binary Search ---\n");
    printf("Result Index: %d\n", indexBinary);
    printf("Total Comparisons: %d\n\n", comparisonsBinary);

    printf("--- Ternary Search ---\n");
    printf("Result Index: %d\n", indexTernary);
    printf("Total Comparisons: %d\n", comparisonsTernary);

    free(arr);
    return 0;
}