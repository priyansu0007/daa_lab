#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Interval;

void merge(Interval arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Interval *L = (Interval *)malloc(n1 * sizeof(Interval));
    Interval *R = (Interval *)malloc(n2 * sizeof(Interval));
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].x <= R[j].x) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L);
    free(R);
}

void mergeSort(Interval arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int mergeIntervals(Interval arr[], int n) {
    if (n <= 0) return 0;
    mergeSort(arr, 0, n - 1);
    int index = 0;
    for (int i = 1; i < n; i++) {
        if (arr[index].y >= arr[i].x) {
            if (arr[i].y > arr[index].y) {
                arr[index].y = arr[i].y;
            }
        } else {
            index++;
            arr[index] = arr[i];
        }
    }
    return index + 1;
}

int main() {
    int n;
    printf("Enter the number of intervals: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;
    Interval *arr = (Interval *)malloc(n * sizeof(Interval));
    printf("Enter the intervals (x y):\n");
    for (int i = 0; i < n; i++) {
        printf("Interval %d: ", i + 1);
        scanf("%d %d", &arr[i].x, &arr[i].y);
        if (arr[i].x > arr[i].y) {
            int temp = arr[i].x;
            arr[i].x = arr[i].y;
            arr[i].y = temp;
        }
    }
    int merged_count = mergeIntervals(arr, n);
    printf("\nMerged Intervals: {");
    for (int i = 0; i < merged_count; i++) {
        printf("(%d, %d)", arr[i].x, arr[i].y);
        if (i < merged_count - 1) printf(", ");
    }
    printf("}\n");
    free(arr);
    return 0;
}