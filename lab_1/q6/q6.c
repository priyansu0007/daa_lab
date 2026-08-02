#include <stdio.h>
#include <stdbool.h>

#define MAX_VALUE 1000

// Function to check for duplicate elements using a hash array
bool hasDuplicates(int arr[], int n) {
    int hash[MAX_VALUE + 1] = {0};

    for (int i = 0; i < n; i++) {

        if (hash[arr[i]] == 1) {
            return true;
        }

        hash[arr[i]] = 1;
    }

    return false;
}

int main() {
    int arr[] = {45, 12, 89, 34, 12, 7, 99};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (hasDuplicates(arr, n))
        printf("The array contains duplicates.\n");
    else
        printf("All elements in the array are unique.\n");

    return 0;
}