#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to calculate and store the trajectory using dynamic memory
unsigned long long* get_collatz_path(unsigned long long n, int *path_length) {
    int capacity = 100; // Start with some initial capacity
    
    // Dynamically allocate memory for the path array
    unsigned long long *path = (unsigned long long*)malloc(capacity * sizeof(unsigned long long));
    if (path == NULL) {
        return NULL; 
    }
    
    int count = 0;
    path[count++] = n;
    
    while (n != 1) {
        // Prevent integer overflow before computing 3n + 1
        if (n % 2 != 0 && n > (ULLONG_MAX - 1) / 3) {
            printf("\n[Warning] Integer overflow detected at %llu! Sequence aborted to prevent crash.\n", n);
            break;
        }
        
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        
        // If we run out of allocated space, reallocate more memory
        if (count >= capacity) {
            capacity *= 2; // Double the size
            unsigned long long *temp = (unsigned long long*)realloc(path, capacity * sizeof(unsigned long long));
            if (temp == NULL) {
                free(path);
                return NULL;
            }
            path = temp;
        }
        
        path[count++] = n;
    }
    
    *path_length = count; // Pass the final length back via pointer
    return path;
}

// Function to find the longest sequence in a given interval
void analyze_interval(unsigned long long a, unsigned long long b) {
    unsigned long long max_start = a;
    int max_steps = 0;
    
    printf("\nAnalyzing interval [%llu, %llu]...\n", a, b);
    
    for (unsigned long long i = a; i <= b; i++) {
        unsigned long long n = i;
        int steps = 0;
        
        while (n != 1) {
            // Basic overflow check
            if (n % 2 != 0 && n > (ULLONG_MAX - 1) / 3) break; 
            
            if (n % 2 == 0) {
                n /= 2;
            } else {
                n = 3 * n + 1;
            }
            steps++;
        }
        
        if (steps > max_steps) {
            max_steps = steps;
            max_start = i;
        }
    }
    
    printf("Longest sequence in this interval starts at %llu, which takes %d steps to reach 1.\n", max_start, max_steps);
}

int main() {
    unsigned long long n, a, b;
    
    printf("--- Collatz Conjecture Explorer ---\n");
    printf("Enter a starting integer (n >= 1) to view its trajectory: ");
    if (scanf("%llu", &n) != 1 || n < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    
    int length = 0;
    // We pass the memory address of 'length' so the function can modify it
    unsigned long long *path = get_collatz_path(n, &length);
    
    if (path != NULL) {
        printf("\nTrajectory for %llu:\n", n);
        for (int i = 0; i < length; i++) {
            printf("%llu ", path[i]);
            // Print a newline every 10 numbers so it doesn't flood the terminal horizontally
            if ((i + 1) % 10 == 0) printf("\n"); 
        }
        printf("\n\nTotal steps to reach 1: %d\n", length - 1);
        
        // Don't forget to free the dynamically allocated memory!
        free(path); 
    } else {
        printf("Memory allocation failed!\n");
    }
    
    printf("\n-----------------------------------\n");
    printf("Now, let's analyze an interval [a, b].\n");
    printf("Enter start of interval (a): ");
    scanf("%llu", &a);
    printf("Enter end of interval (b): ");
    scanf("%llu", &b);
    
    if (a < 1 || b < a) {
        printf("Invalid interval provided.\n");
        return 1;
    }
    
    analyze_interval(a, b);
    
    return 0;
}