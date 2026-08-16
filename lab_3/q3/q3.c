#include <stdio.h>
#include <stdlib.h>

struct Pair {
    int min;
    int max;
};
// Function to find min and max using Divide and Conquer
struct Pair getMinMax(int arr[], int low, int high) {
    struct Pair result, leftResult, rightResult;
    int mid;
    // Case 1: Only one element
    if (low == high) {
        result.max = arr[low];
        result.min = arr[low];
        return result;
    }

    // Case 2: Exactly two elements
    if (high == low + 1) {
        if (arr[low] > arr[high]) {
            result.max = arr[low];
            result.min = arr[high];
        } else {
            result.max = arr[high];
            result.min = arr[low];
        }
        return result;
    }

    // Case 3: More than two elements (Divide and Conquer)
    mid = low + (high - low) / 2;
    leftResult = getMinMax(arr, low, mid);
    rightResult = getMinMax(arr, mid + 1, high);

    // Combine results
    result.min = (leftResult.min < rightResult.min) ? leftResult.min : rightResult.min;
    result.max = (leftResult.max > rightResult.max) ? leftResult.max : rightResult.max;

    return result;
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d",&n);
    int* arr=(int *)malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        printf("Enter the element: ");
        scanf("%d",&arr[i]);
    }
    
    struct Pair minmax = getMinMax(arr, 0, n - 1);

    printf("Array elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Minimum element: %d\n", minmax.min);
    printf("Maximum element: %d\n", minmax.max);

    return 0;
}