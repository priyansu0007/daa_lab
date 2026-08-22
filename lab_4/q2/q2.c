#include <stdio.h>
#include <stdlib.h>

// Forward declarations / function prototypes
int bSearch(int* arr, int n, int target);
void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

void setTwoSum(int* s1, int* s2, int n, int x) {
    // Sort s2: right index is n - 1
    mergeSort(s2, 0, n - 1);

    int found = 0;
    for (int i = 0; i < n; i++) {
        int target = x - s1[i];
        int idx = bSearch(s2, n, target);

        if (idx != -1) {
            printf("Elements found: %d (from Set 1) + %d (from Set 2) = %d\n", s1[i], s2[idx], x);
            found = 1;
            break; // Stop after finding the first valid pair
        }
    }

    if (!found) {
        printf("No such elements found!\n");
    }
}

int bSearch(int* arr, int n, int target) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] > target) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1;
}

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1], rightArr[n2];

    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    int* s1 = (int *)malloc(n * sizeof(int));
    int* s2 = (int *)malloc(n * sizeof(int));

    if (s1 == NULL || s2 == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(s1);
        free(s2);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter the element %d of set 1: ", i + 1);
        scanf("%d", &s1[i]);
    }
    for (int i = 0; i < n; i++) {
        printf("Enter the element %d of set 2: ", i + 1);
        scanf("%d", &s2[i]);
    }

    int x;
    printf("Enter the value of x: ");
    scanf("%d", &x);

    setTwoSum(s1, s2, n, x);

    // Free heap memory
    free(s1);
    free(s2);

    return 0;
}