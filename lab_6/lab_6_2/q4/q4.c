#include <stdio.h>

// Global variable to keep track of the total cost
int total_cost = 0;

// Reverses the subarray arr[i...j] and adds to the total cost
void reverse(int arr[], int i, int j) {
    if (i >= j) return;
    total_cost += (j - i + 1); // Cost = length of the reversal
    
    while (i < j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }
}

// Rotates the subarray arr[start...end] such that the elements 
// in arr[mid...end] come before the elements in arr[start...mid-1]
void rotate(int arr[], int start, int mid, int end) {
    if (start >= mid || mid > end) return;
    // Rotation using 3 reversals
    reverse(arr, start, mid - 1);
    reverse(arr, mid, end);
    reverse(arr, start, end);
}

// Binary search to find the insertion point in block B
int binary_search(int arr[], int low, int high, int key) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return low;
}

// In-place merge using rotations
void merge(int arr[], int start, int mid, int end) {
    if (start >= mid || mid > end) return;

    // Find the middle of the first half (Block A)
    int mid_A = start + (mid - 1 - start) / 2;
    int val_A = arr[mid_A];

    // Find where val_A fits in the second half (Block B)
    int split_B = binary_search(arr, mid, end, val_A);

    // Calculate how many elements belong to B1
    int elements_B1 = split_B - mid;
    
    // Rotate A2 and B1
    // A2 is from mid_A to mid - 1
    // B1 is from mid to split_B - 1
    rotate(arr, mid_A, mid, split_B - 1);

    // Calculate the new index of the pivot (val_A)
    int new_mid = mid_A + elements_B1;

    // Recursively merge the left and right partitions
    merge(arr, start, mid_A, new_mid - 1);
    merge(arr, new_mid + 1, split_B, end);
}

// The Divide and Conquer sorting function
void merge_sort(int arr[], int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        merge_sort(arr, start, mid);
        merge_sort(arr, mid + 1, end);
        // Merge the two sorted halves
        merge(arr, start, mid + 1, end);
    }
}

int main() {
    int n;
    printf("Enter the number of elements for the permutation: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Invalid size.\n");
        return 0;
    }

    int p[n];
    printf("Enter the permutation (integers separated by space):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    // Reset cost counter and sort
    total_cost = 0;
    merge_sort(p, 0, n - 1);

    printf("\nSorted Permutation: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", p[i]);
    }
    
    printf("\nTotal Reversal Cost: %d\n", total_cost);

    return 0;
}