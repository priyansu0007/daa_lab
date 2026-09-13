#include <stdio.h>
#include <limits.h>
#include <math.h>

int reves_puzzle(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    int dp[n + 1];
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 3; 

    for (int i = 3; i <= n; i++) {
        dp[i] = INT_MAX;
        for (int k = 1; k < i; k++) {
            int moves = 2 * dp[k] + (1 << (i - k)) - 1;
            if (moves < dp[i]) {
                dp[i] = moves;
            }
        }
    }
    return dp[n];
}

int main() {
    int n = 8;
    printf("Minimum moves for %d disks is: %d\n", n, reves_puzzle(n));
    return 0;
}