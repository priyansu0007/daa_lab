#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NORMAL_WEIGHT 10
#define DEFECTIVE_WEIGHT 9 // Lighter than normal

/**
 * Recursive Divide and Conquer Algorithm
 * Returns the index of the defective coin, or -1 if all coins are perfect.
 */
int findDefectiveCoin(int coins[], int low, int high, int known_good, int confirmed, int *weighings) {
    int len = high - low + 1;

    // Base Case: 1 coin remaining
    if (len == 1) {
        if (confirmed) {
            // We already know a defective coin exists in this branch
            return low;
        } else {
            // No defective coin was confirmed yet. We must verify this last coin 
            // against a known perfect coin to see if it's actually defective.
            (*weighings)++;
            if (coins[low] < coins[known_good]) {
                return low;
            } else {
                return -1; // Coin is perfect, no defective coin exists
            }
        }
    }

    // Divide: Split the current segment into two equal halves
    int half = len / 2;
    int sumA = 0, sumB = 0;
    
    // Calculate weight of Set A (Left half)
    for (int i = 0; i < half; i++) {
        sumA += coins[low + i];
    }
    
    // Calculate weight of Set B (Right half)
    for (int i = 0; i < half; i++) {
        sumB += coins[low + half + i];
    }
    
    (*weighings)++; // Increment weighing count for comparing Set A and Set B

    // Conquer
    if (sumA == sumB) {
        // Both halves balance perfectly. 
        // We now know for a fact that any coin in Set A is a "known good" coin.
        known_good = low; 
        
        if (len % 2 == 0) {
            // Even number of coins and they balanced. No leftover coin.
            return -1; 
        } else {
            // Odd number of coins. The only suspect left is the odd one out at the end.
            return findDefectiveCoin(coins, high, high, known_good, confirmed, weighings);
        }
    } 
    else if (sumA < sumB) {
        // Set A is lighter. Defective coin is definitely in Set A.
        return findDefectiveCoin(coins, low, low + half - 1, -1, 1, weighings);
    } 
    else {
        // Set B is lighter. Defective coin is definitely in Set B.
        return findDefectiveCoin(coins, low + half, low + 2 * half - 1, -1, 1, weighings);
    }
}

/**
 * Helper function to run a specific test case
 */
void runTestCase(int n, int defective_index) {
    int *coins = (int *)malloc(n * sizeof(int));
    
    // Initialize all coins with normal weight
    for (int i = 0; i < n; i++) {
        coins[i] = NORMAL_WEIGHT;
    }
    
    // Insert defective coin if index is valid (>= 0)
    if (defective_index >= 0 && defective_index < n) {
        coins[defective_index] = DEFECTIVE_WEIGHT;
    }

    int weighings = 0;
    
    // Start algorithm
    // known_good is initialized to -1 (none known yet)
    // confirmed is initialized to 0 (false)
    int result = findDefectiveCoin(coins, 0, n - 1, -1, 0, &weighings);

    printf("Total Coins (N): %d\n", n);
    if (defective_index == -1) {
        printf("Scenario: ALL coins are perfect (No defective coin).\n");
    } else {
        printf("Scenario: Defective coin is at index %d.\n", defective_index);
    }
    
    printf("Algorithm Found: %d\n", result);
    printf("Weighings Used:  %d\n", weighings);
    
    // Calculate log2(n) for comparison
    int expected_max_steps = (int)ceil(log2(n)) + 1; // log2(n) + c, where c is at most 1 or 2
    printf("Theoretical max steps (ceil(log2 N) + 1): %d\n", expected_max_steps);
    
    if (result == defective_index) {
        printf("Status: SUCCESS\n\n");
    } else {
        printf("Status: FAILED\n\n");
    }

    free(coins);
}

int main() {
    printf("==========================================\n");
    printf("   Defective Coin Quality Control Test    \n");
    printf("==========================================\n\n");

    // Test 1: Even number of coins, defective coin present
    runTestCase(16, 11);

    // Test 2: Odd number of coins, defective coin present (falls in half)
    runTestCase(15, 4);

    // Test 3: Odd number of coins, defective coin is the last one left out
    runTestCase(15, 14);

    // Test 4: All coins are perfect (even n)
    runTestCase(16, -1);

    // Test 5: All coins are perfect (odd n)
    runTestCase(15, -1);

    // Test 6: Large dataset to prove O(log N)
    runTestCase(100000, 99999);

    return 0;
}