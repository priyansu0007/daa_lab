#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Standard 2-Way Merge Sort ---
void merge_2way(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
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

void merge_sort_2way(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_2way(arr, left, mid);
        merge_sort_2way(arr, mid + 1, right);
        merge_2way(arr, left, mid, right);
    }
}

// --- Modified 3-Way Merge Sort ---
void merge_3way(int arr[], int left, int mid1, int mid2, int right) {
    int n1 = mid1 - left + 1;
    int n2 = mid2 - mid1;
    int n3 = right - mid2;
    
    int *L = malloc(n1 * sizeof(int));
    int *M = malloc(n2 * sizeof(int));
    int *R = malloc(n3 * sizeof(int));
    
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) M[i] = arr[mid1 + 1 + i];
    for (int i = 0; i < n3; i++) R[i] = arr[mid2 + 1 + i];
    
    int i = 0, j = 0, k = 0, l = left;
    
    while (i < n1 && j < n2 && k < n3) {
        if (L[i] <= M[j] && L[i] <= R[k]) arr[l++] = L[i++];
        else if (M[j] <= L[i] && M[j] <= R[k]) arr[l++] = M[j++];
        else arr[l++] = R[k++];
    }
    
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) arr[l++] = L[i++];
        else arr[l++] = M[j++];
    }
    while (j < n2 && k < n3) {
        if (M[j] <= R[k]) arr[l++] = M[j++];
        else arr[l++] = R[k++];
    }
    while (i < n1 && k < n3) {
        if (L[i] <= R[k]) arr[l++] = L[i++];
        else arr[l++] = R[k++];
    }
    
    while (i < n1) arr[l++] = L[i++];
    while (j < n2) arr[l++] = M[j++];
    while (k < n3) arr[l++] = R[k++];
    
    free(L);
    free(M);
    free(R);
}

void merge_sort_3way(int arr[], int left, int right) {
    if (left < right) {
        int len = right - left + 1;
        
        // Base case to prevent infinite recursion and 0-size allocations
        if (len < 3) {
            if (len == 2 && arr[left] > arr[right]) {
                int temp = arr[left];
                arr[left] = arr[right];
                arr[right] = temp;
            }
            return;
        }
        
        int third = len / 3;
        int mid1 = left + third - 1;
        int mid2 = left + 2 * third - 1;
        
        merge_sort_3way(arr, left, mid1);
        merge_sort_3way(arr, mid1 + 1, mid2);
        merge_sort_3way(arr, mid2 + 1, right);
        
        merge_3way(arr, left, mid1, mid2, right);
    }
}

int main() {
    srand(time(NULL));
    
    // Open the file to write plotting data
    FILE *fp = fopen("merge.dat", "w");
    if (fp == NULL) {
        printf("Error: Could not open merge.dat for writing.\n");
        return 1;
    }
    
    // Add a comment header for Gnuplot
    fprintf(fp, "# Array_Size 2-Way_Time(s) 3-Way_Time(s)\n");
    printf("Running tests and generating merge.dat...\n");
    
    // Test sizes from 10,000 to 200,000 in steps of 10,000
    for (int n = 10000; n <= 200000; n += 10000) {
        int *arr_2way = malloc(n * sizeof(int));
        int *arr_3way = malloc(n * sizeof(int));
        
        for (int i = 0; i < n; i++) {
            int val = rand() % 100000;
            arr_2way[i] = val;
            arr_3way[i] = val;
        }
        
        // Measure 2-Way
        clock_t start_2way = clock();
        merge_sort_2way(arr_2way, 0, n - 1);
        clock_t end_2way = clock();
        double time_2way = ((double)(end_2way - start_2way)) / CLOCKS_PER_SEC;
        
        // Measure 3-Way
        clock_t start_3way = clock();
        merge_sort_3way(arr_3way, 0, n - 1);
        clock_t end_3way = clock();
        double time_3way = ((double)(end_3way - start_3way)) / CLOCKS_PER_SEC;
        
        // Write the data row to the file (space separated for gnuplot)
        fprintf(fp, "%d %f %f\n", n, time_2way, time_3way);
        printf("Completed array size: %d\n", n);
        
        free(arr_2way);
        free(arr_3way);
    }
    
    fclose(fp);
    printf("Success! Data written to merge.dat.\n");
    
    return 0;
}