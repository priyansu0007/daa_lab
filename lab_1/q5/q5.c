#include <stdio.h>

// Function to find the index of the first '1'
int findTransitionPoint(int arr[], int n) {
    int low = 0;
    int high = n - 1;
    int result = -1; // Default if no '1' is found

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == 1) {
            result = mid;      // Record the position
            high = mid - 1;    // Look left to see if there's an earlier '1'
        } else {
            low = mid + 1;     // Look right because mid is '0'
        }
    }
    return result;
}

int main() {
    int arr[] = {0, 0, 0, 0, 1, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    int point = findTransitionPoint(arr, n);

    if (point != -1)
        printf("Transition point found at index: %d\n", point);
    else
        printf("No transition point (array contains only 0s).\n");

    return 0;
}