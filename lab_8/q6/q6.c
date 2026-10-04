#include <stdio.h>
#include <string.h>

// Global variables to avoid stack overflow for large strings
int dp[1005][1005];

// A simple helper function to find the minimum of three numbers
int min3(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

int main() {
    char A[1005], B[1005];
    
    printf("Enter first string (A): ");
    scanf("%s", A);
    
    printf("Enter second string (B): ");
    scanf("%s", B);
    
    int m = strlen(A);
    int n = strlen(B);
    
    // Base cases: transforming to an empty string means dropping all characters,
    // transforming from an empty string means inserting all characters.
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;
    
    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i-1] == B[j-1]) {
                // Characters match, no new operation needed
                dp[i][j] = dp[i-1][j-1];
            } else {
                // Find the best operation: Replace, Delete, or Insert
                dp[i][j] = 1 + min3(dp[i-1][j-1], // Replace
                                    dp[i-1][j],   // Delete from A
                                    dp[i][j-1]);  // Insert into A
            }
        }
    }
    
    printf("\nMinimum Edit Distance: %d\n", dp[m][n]);
    
    // Traceback to find the operations
    printf("Traceback Operations:\n");
    
    // We will store the steps in an array of strings to print them in the right order
    char operations[2005][50];
    int step = 0;
    
    int i = m, j = n;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && A[i-1] == B[j-1]) {
            sprintf(operations[step++], "Match '%c'", A[i-1]);
            i--;
            j--;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i-1][j-1] + 1) {
            sprintf(operations[step++], "Replace '%c' with '%c'", A[i-1], B[j-1]);
            i--;
            j--;
        } else if (i > 0 && dp[i][j] == dp[i-1][j] + 1) {
            sprintf(operations[step++], "Delete '%c'", A[i-1]);
            i--;
        } else if (j > 0 && dp[i][j] == dp[i][j-1] + 1) {
            sprintf(operations[step++], "Insert '%c'", B[j-1]);
            j--;
        }
    }
    
    // Print the steps in reverse order (from start of string to end)
    for (int k = step - 1; k >= 0; k--) {
        printf("- %s\n", operations[k]);
    }
    
    return 0;
}