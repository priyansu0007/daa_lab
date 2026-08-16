#include <stdio.h>
#include <stdlib.h>

// Function to perform Selection Sort and return the number of comparisons
int selectionSort(int arr[], int n) {
    int comparisons = 0;
    
    // Outer loop runs for first n-1 elements
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        
        // Inner loop finds the smallest element in remaining array
        for (int j = i + 1; j < n; j++) {
            comparisons++; // Count every comparison
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        // Swap the found minimum element with the first element of the unsorted part
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
    
    return comparisons;
}

// Helper function to print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    int *arrBest = (int*)malloc(n * sizeof(int));
    int *arrWorst = (int*)malloc(n * sizeof(int));

    // Generate a best-case array (already sorted) and worst-case (reverse sorted)
    for (int i = 0; i < n; i++) {
        arrBest[i] = i + 1;
        arrWorst[i] = n - i;
    }

    printf("\n--- Best Case (Already Sorted) ---\n");
    // printf("Initial: "); printArray(arrBest, n);
    int compBest = selectionSort(arrBest, n);
    printf("Comparisons made: %d\n", compBest);

    printf("\n--- Worst Case (Reverse Sorted) ---\n");
    // printf("Initial: "); printArray(arrWorst, n);
    int compWorst = selectionSort(arrWorst, n);
    printf("Comparisons made: %d\n", compWorst);

    // Calculate theoretical comparisons: n * (n - 1) / 2
    int theoretical = (n * (n - 1)) / 2;
    printf("\n--- Validation ---\n");
    printf("Theoretical n(n-1)/2 comparisons: %d\n", theoretical);
    
    if (compBest == theoretical && compWorst == theoretical) {
        printf("Claim Validated: Best-case and Worst-case time complexity are both Theta(n^2).\n");
    }

    free(arrBest);
    free(arrWorst);

    return 0;
}