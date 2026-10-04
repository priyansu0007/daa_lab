#include <stdio.h>

int main() {
    int n, target;
    int coins[100];
    
    // Using long long because the number of combinations can get huge
    long long dp[10005] = {0}; 
    
    printf("Enter number of coins: ");
    scanf("%d", &n);
    
    printf("Enter the coins: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }
    
    printf("Enter target amount: ");
    scanf("%d", &target);
    
    // Base case: There is exactly 1 way to make amount 0 (pick no coins)
    dp[0] = 1;
    
    // Outer loop over coins ensures we only count distinct combinations,
    // avoiding permutations like treating 1+2 and 2+1 as different.
    for(int i = 0; i < n; i++) {
        for(int j = coins[i]; j <= target; j++) {
            dp[j] = dp[j] + dp[j - coins[i]];
        }
    }
    
    printf("Total number of ways: %lld\n", dp[target]);
    
    return 0;
}