#include <stdio.h>
#include <string.h>

// Making the dp table global so it doesn't blow up the stack memory
// 1005 is just a safe upper limit for string lengths up to 1000
int dp[1005][1005]; 

int main() {
    char X[1005], Y[1005];
    char lcs_str[1005];
    
    printf("Enter first string: ");
    scanf("%s", X);
    
    printf("Enter second string: ");
    scanf("%s", Y);
    
    int m = strlen(X);
    int n = strlen(Y);
    
    // Fill the dp table
    for(int i = 0; i <= m; i++) {
        for(int j = 0; j <= n; j++) {
            if(i == 0 || j == 0) {
                dp[i][j] = 0; // Base case: one string is empty
            } else if(X[i-1] == Y[j-1]) {
                // Characters match, add 1 to the diagonal value
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                // Characters don't match, take the max from left or top cell
                if(dp[i-1][j] > dp[i][j-1]) {
                    dp[i][j] = dp[i-1][j];
                } else {
                    dp[i][j] = dp[i][j-1];
                }
            }
        }
    }
    
    int length = dp[m][n];
    printf("Length of LCS: %d\n", length);
    
    if(length == 0) {
        printf("The LCS is: (none)\n");
        return 0;
    }
    
    // Backtrack to find the actual string
    int index = length;
    lcs_str[index] = '\0'; // End the string
    
    int i = m, j = n;
    while(i > 0 && j > 0) {
        if(X[i-1] == Y[j-1]) {
            // It's a match, meaning this character is part of the LCS
            lcs_str[index-1] = X[i-1];
            i--;
            j--;
            index--;
        } else if(dp[i-1][j] > dp[i][j-1]) {
            // Move in the direction of the larger value
            i--;
        } else {
            j--;
        }
    }
    
    printf("The LCS is: %s\n", lcs_str);
    
    return 0;
}