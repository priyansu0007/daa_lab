#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main() {
    int n;
    printf("Enter number of intervals: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;
    int *L = (int *)malloc(n * sizeof(int));
    int *R = (int *)malloc(n * sizeof(int));
    printf("Enter intervals (l r):\n");
    for (int k = 0; k < n; k++) {
        scanf("%d %d", &L[k], &R[k]);
        if (L[k] > R[k]) {
            int temp = L[k];
            L[k] = R[k];
            R[k] = temp;
        }
    }
    mergeSort(L, 0, n - 1);
    mergeSort(R, 0, n - 1);
    int i = 0, j = 0, max_overlap = 0, current_overlap = 0, best_point = 0;
    while (i < n && j < n) {
        if (L[i] <= R[j]) {
            current_overlap++;
            if (current_overlap > max_overlap) {
                max_overlap = current_overlap;
                best_point = L[i];
            }
            i++;
        } else {
            current_overlap--;
            j++;
        }
    }
    printf("Point %d is in the largest number of intervals (%d).\n", best_point, max_overlap);
    free(L);
    free(R);
    return 0;
}