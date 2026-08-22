#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++) L[i] = arr[left + i];
    for (j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

bool binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return true;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}

bool kSum(int arr[], int n, int k, int start_index, int target) {
    if (k == 1) {
        return binarySearch(arr, start_index, n - 1, target);
    }

    for (int i = start_index; i <= n - k; i++) {
        if (kSum(arr, n, k - 1, i + 1, target - arr[i])) {
            return true;
        }
    }
    return false;
}

int main() {
    int n, T, k;

    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    int *S = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &S[i]);
    }

    printf("Enter the value of target sum (T): ");
    scanf("%d", &T);

    printf("Enter the value of elements to sum (k): ");
    scanf("%d", &k);

    mergeSort(S, 0, n - 1);

    printf("\nSorted Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", S[i]);
    }
    printf("\n\n");

    if (k > n || k <= 0) {
        printf("Result: Invalid value for k.\n");
    } else if (kSum(S, n, k, 0, T)) {
        printf("Result: YES, there are %d elements that sum up to %d.\n", k, T);
    } else {
        printf("Result: NO such %d elements exist.\n", k);
    }

    free(S);
    return 0;
}