#include <stdio.h>

int main() {
    int n;
    int arr[1005];
    int dp[1005]; 
    int max_sum = 0;
    
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Maximum sum: 0\n");
        return 0;
    }
    
    printf("Enter the elements: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        // The minimum possible sum of an increasing subsequence ending at i 
        // is just the element itself
        dp[i] = arr[i]; 
    }
    
    // Calculate max sum for every possible increasing subsequence
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < i; j++) {
            // Check if it's strictly increasing AND if adding arr[i] to the 
            // sequence ending at arr[j] gives us a bigger sum than we already have
            if(arr[i] > arr[j] && dp[i] < dp[j] + arr[i]) {
                dp[i] = dp[j] + arr[i];
            }
        }
    }
    
    // The sequence with the maximum sum could end at any index, 
    // so we search the whole dp array to find the largest value.
    for(int i = 0; i < n; i++) {
        if(dp[i] > max_sum) {
            max_sum = dp[i];
        }
    }
    
    printf("Maximum sum of increasing subsequence: %d\n", max_sum);
    
    return 0;
}