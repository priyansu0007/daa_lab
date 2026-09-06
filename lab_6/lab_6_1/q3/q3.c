#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

void lcs(char *X, char *Y) {
    int m = strlen(X);
    int n = strlen(Y);
    int dp[m + 1][n + 1];

    // Build the dp table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int index = dp[m][n];
    printf("Length of Longest Common Subsequence: %d\n", index);

    // Create a character array to store the LCS string
    char lcs_str[index + 1];
    lcs_str[index] = '\0'; // Set the terminating null byte

    // Backtrack to find the sequence
    int i = m, j = n;
    while (i > 0 && j > 0) {
        // If current characters match, they are part of the LCS
        if (X[i - 1] == Y[j - 1]) {
            lcs_str[index - 1] = X[i - 1]; 
            i--;
            j--;
            index--; 
        }
        // If they don't match, move to the cell with the higher value
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("The Subsequence: %s\n", lcs_str);
}

int main() {
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";

    printf("String 1: %s\n", X);
    printf("String 2: %s\n", Y);
    lcs(X, Y);

    return 0;
}