#include <stdio.h>

int main() {
    int n;
    int price[1005]; // Array to store prices, 1-indexed for convenience
    int dp[1005] = {0}; // Stores the maximum revenue for a rod of length i
    int first_cut[1005] = {0}; // Stores the first piece cut off to achieve the max revenue
    
    printf("Enter the length of the rod (n): ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Max revenue: 0\n");
        return 0;
    }
    
    printf("Enter the prices for pieces of length 1 to %d:\n", n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &price[i]);
    }
    
    // dp[0] is automatically 0 (initialized above)
    // We compute the maximum revenue for every length from 1 up to n
    for(int i = 1; i <= n; i++) {
        int max_val = -1;
        
        // Try cutting a piece of length j from the rod of length i
        for(int j = 1; j <= i; j++) {
            if (price[j] + dp[i - j] > max_val) {
                max_val = price[j] + dp[i - j];
                // Record the length of the piece we just chose to cut
                first_cut[i] = j; 
            }
        }
        dp[i] = max_val;
    }
    
    printf("\nMaximum Revenue: %d\n", dp[n]);
    
    printf("Optimal piece lengths: ");
    int curr_length = n;
    while(curr_length > 0) {
        printf("%d ", first_cut[curr_length]);
        // Subtract the piece we just cut off from the remaining length
        curr_length = curr_length - first_cut[curr_length];
    }
    printf("\n");
    
    return 0;
}