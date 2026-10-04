#include <stdio.h>
#include <stdlib.h>

int minCoins(int coins[], int n, int V) {
    // dp array stores the minimum number of coins required for each amount up to V
    int *dp = (int *)malloc((V + 1) * sizeof(int));
    
    // Base case: 0 amount requires 0 coins
    dp[0] = 0;

    // Initialize all dp values to V + 1. We use V + 1 instead of INT_MAX 
    // to prevent integer overflow when adding 1 later.
    for (int i = 1; i <= V; i++) {
        dp[i] = V + 1; 
    }

    // Compute minimum coins required for all values from 1 to V
    for (int i = 1; i <= V; i++) {
        // Try every coin denomination for the current amount i
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i) {
                int sub_res = dp[i - coins[j]];
                if (sub_res != V + 1 && sub_res + 1 < dp[i]) {
                    dp[i] = sub_res + 1;
                }
            }
        }
    }

    int result = dp[V];
    free(dp);

    // If dp[V] is still V + 1, it means the amount cannot be made
    if (result > V) {
        return -1;
    }
    
    return result;
}

int main() {
    int n, V;

    printf("Enter the number of coin denominations: ");
    if (scanf("%d", &n) != 1) return 1;

    // Dynamically allocate memory for the coins array based on user input
    int *coins = (int *)malloc(n * sizeof(int));
    printf("Enter the %d coin denominations separated by space:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &coins[i]) != 1) return 1;
    }

    printf("Enter the target amount: ");
    if (scanf("%d", &V) != 1) return 1;

    int min_coins = minCoins(coins, n, V);

    if (min_coins == -1) {
        printf("Output: -1 (Amount cannot be made up by any combination)\n");
    } else {
        printf("Minimum coins required: %d\n", min_coins);
    }

    free(coins);
    return 0;
}