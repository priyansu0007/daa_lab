#include <stdio.h>

int main() {
    int n;
    int arr[1005];
    int dp[1005];
    int max_len = 0;
    
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Length of LIS: 0\n");
        return 0;
    }
    
    printf("Enter the elements: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        // Base case: every single element is an increasing sequence of length 1
        dp[i] = 1; 
    }
    
    // Build the dp array from left to right
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < i; j++) {
            // Check if arr[i] can extend the increasing sequence ending at arr[j]
            if(arr[i] > arr[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
            }
        }
    }
    
    // The length of the longest increasing subsequence could end anywhere,
    // so we need to find the maximum value in our dp array.
    for(int i = 0; i < n; i++) {
        if(dp[i] > max_len) {
            max_len = dp[i];
        }
    }
    
    printf("Length of Longest Increasing Subsequence: %d\n", max_len);
    
    return 0;
}