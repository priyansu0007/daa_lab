#include <stdio.h>
#include <stdlib.h>

typedef struct pair {
    int val;
    char col;
} pair;

// Stable bucket/counting sort: O(n) Time, O(n) Auxiliary Space
void sortColorsPreserveValues(pair *arr, int size) {
    if (arr == NULL || size <= 1) return;
    pair *result = (pair *)malloc(size * sizeof(pair));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed for result buffer.\n");
        return;
    }

    int redCount = 0;
    int blueCount = 0;

    // Pass 1: Count occurrences of each color
    for (int i = 0; i < size; i++) {
        char c = arr[i].col;
        if (c == 'r' || c == 'R') {
            redCount++;
        } else if (c == 'b' || c == 'B') {
            blueCount++;
        }
    }

    // Set starting indices for each color block
    int rIdx = 0;
    int bIdx = redCount;
    int yIdx = redCount + blueCount;

    // Pass 2: Place elements into respective buckets in forward order (maintains stability)
    for (int i = 0; i < size; i++) {
        char c = arr[i].col;
        if (c == 'r' || c == 'R') {
            result[rIdx++] = arr[i];
        } else if (c == 'b' || c == 'B') {
            result[bIdx++] = arr[i];
        } else if (c == 'y' || c == 'Y') {
            result[yIdx++] = arr[i];
        }
    }

    // Copy sorted elements back to original array
    for (int i = 0; i < size; i++) {
        arr[i] = result[i];
    }

    // Free the dynamically allocated auxiliary buffer
    free(result);
}

void printPairs(const pair *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("(%d, %c) ", arr[i].val, arr[i].col);
    }
    printf("\n");
}

int main() {
    int size = 6;

    // Dynamically allocate the main array of pairs
    pair *items = (pair *)malloc(size * sizeof(pair));
    if (items == NULL) {
        fprintf(stderr, "Memory allocation failed for items array.\n");
        return 1;
    }

    // Input data: pre-sorted in ascending order by value
    items[0] = (pair){2,  'r'};
    items[1] = (pair){5,  'y'};
    items[2] = (pair){7,  'r'};
    items[3] = (pair){10, 'y'};
    items[4] = (pair){15, 'b'};
    items[5] = (pair){42, 'b'};

    printf("Original (sorted by val): ");
    printPairs(items, size);

    sortColorsPreserveValues(items, size);

    printf("Sorted (Color -> Value):  ");
    printPairs(items, size);

    // Free the main array
    free(items);
    return 0;
}