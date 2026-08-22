#include <stdio.h>
#include <stdlib.h>

// Comparator function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void findPeakPartyTime(int entry[], int exit[], int n) {
    // Step 1: Sort both arrays -> O(n log n)
    qsort(entry, n, sizeof(int), compare);
    qsort(exit, n, sizeof(int), compare);

    int current_people = 0;
    int max_people = 0;
    int time_of_max = 0;
    
    // Step 2 & 3: Two-pointer traversal -> O(n)
    int i = 0, j = 0;
    while (i < n && j < n) {
        if (entry[i] < exit[j]) {
            // A person enters
            current_people++;
            
            // Track the peak
            if (current_people > max_people) {
                max_people = current_people;
                time_of_max = entry[i];
            }
            i++; 
        } else {
            // A person exits
            current_people--;
            j++;
        }
    }

    printf("\nAnalysis Complete:\n");
    printf("Maximum people present simultaneously: %d\n", max_people);
    printf("Time when the party peaked: %d\n", time_of_max);
}

int main() {
    int n;

    printf("Enter the total number of people (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    // Allocate memory for separate entry and exit arrays
    int *entry = (int *)malloc(n * sizeof(int));
    int *exit = (int *)malloc(n * sizeof(int));

    printf("Enter the entry and exit times for each person (ai bi):\n");
    for (int k = 0; k < n; k++) {
        printf("Person %d: ", k + 1);
        scanf("%d %d", &entry[k], &exit[k]);
        
        // Input validation based on the problem constraints
        if (entry[k] >= exit[k]) {
            printf("Error: Exit time must be strictly greater than entry time.\n");
            free(entry);
            free(exit);
            return 1;
        }
    }

    findPeakPartyTime(entry, exit, n);

    free(entry);
    free(exit);
    return 0;
}