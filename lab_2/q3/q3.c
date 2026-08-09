#include <stdio.h>
#include <stdlib.h>

// Standard subroutine to merge two sorted arrays
void merge(int* arr1, int size1, int* arr2, int size2, int* result) {
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
    }
    while (i < size1) result[k++] = arr1[i++];
    while (j < size2) result[k++] = arr2[j++];
}

// ==============================================
// METHOD 1: Sequential Merging O(n*k^2)
// ==============================================
int* method1(int** arrays, int k, int n) {
    int* result = (int*)malloc(k * n * sizeof(int));
    int* temp = (int*)malloc(k * n * sizeof(int));

    // Initialize result with the first array
    for (int i = 0; i < n; i++) {
        result[i] = arrays[0][i];
    }

    int current_size = n;
    for (int i = 1; i < k; i++) {
        // Merge current result with the next array
        merge(result, current_size, arrays[i], n, temp);
        current_size += n;
        
        // Copy merged data back into result
        for (int j = 0; j < current_size; j++) {
            result[j] = temp[j];
        }
    }
    
    free(temp);
    return result;
}

// ==============================================
// METHOD 2: Divide & Conquer Merging O(n*k*logk)
// ==============================================
int* method2_recursive(int** arrays, int left, int right, int n) {
    // Base case: Only one array to merge
    if (left == right) {
        int* res = (int*)malloc(n * sizeof(int));
        for(int i = 0; i < n; i++) {
            res[i] = arrays[left][i];
        }
        return res;
    }
    
    int mid = left + (right - left) / 2;
    
    // Recursively divide the arrays into halves
    int* left_merged = method2_recursive(arrays, left, mid, n);
    int* right_merged = method2_recursive(arrays, mid + 1, right, n);

    int left_size = (mid - left + 1) * n;
    int right_size = (right - mid) * n;

    int* final_merged = (int*)malloc((left_size + right_size) * sizeof(int));
    
    // Merge the divided halves
    merge(left_merged, left_size, right_merged, right_size, final_merged);

    free(left_merged);
    free(right_merged);
    
    return final_merged;
}

// Main Driver Function
int main() {
    int k = 4; // Number of arrays
    int n = 3; // Elements per array
    
    // Allocate 2D array representing k arrays of size n
    int** arrays = (int**)malloc(k * sizeof(int*));
    for (int i = 0; i < k; i++) {
        arrays[i] = (int*)malloc(n * sizeof(int));
    }

    // Initialize arrays with sorted dummy data
    arrays[0][0] = 1; arrays[0][1] = 5; arrays[0][2] = 9;
    arrays[1][0] = 2; arrays[1][1] = 6; arrays[1][2] = 10;
    arrays[2][0] = 3; arrays[2][1] = 7; arrays[2][2] = 11;
    arrays[3][0] = 4; arrays[3][1] = 8; arrays[3][2] = 12;

    printf("Input Data (%d arrays of %d elements):\n", k, n);
    for (int i = 0; i < k; i++) {
        printf("Array %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            printf("%d ", arrays[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Test Method 1
    int* result1 = method1(arrays, k, n);
    printf("Method 1 Result: ");
    for (int i = 0; i < k * n; i++) {
        printf("%d ", result1[i]);
    }
    printf("\n");

    // Test Method 2
    int* result2 = method2_recursive(arrays, 0, k - 1, n);
    printf("Method 2 Result: ");
    for (int i = 0; i < k * n; i++) {
        printf("%d ", result2[i]);
    }
    printf("\n");

    // Memory Cleanup
    free(result1);
    free(result2);
    for (int i = 0; i < k; i++) free(arrays[i]);
    free(arrays);

    return 0;
}