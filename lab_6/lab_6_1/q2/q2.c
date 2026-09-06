#include <stdio.h>

// Utility function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve the 0/1 Knapsack problem
int knapsack(int W, int weights[], int profits[], int n) {
    int dp[n + 1][W + 1];

    // Build the dp table in bottom-up manner
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            // Base case: 0 items or 0 capacity
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            }
            // If the weight of the current item is less than or equal to the capacity
            else if (weights[i - 1] <= w) {
                dp[i][w] = max(profits[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            }
            // If the weight of the current item is more than the capacity, exclude it
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // The maximum profit will be at dp[n][W]
    return dp[n][W];
}

int main() {
    int profits[] = {60, 100, 120};
    int weights[] = {10, 20, 30};
    int W = 50; // Knapsack capacity
    int n = sizeof(profits) / sizeof(profits[0]);

    printf("Maximum profit obtained: %d\n", knapsack(W, weights, profits, n));

    return 0;
}