#include <stdio.h>
#include <float.h>

int main() {
    int n;
    // We use a small maximum size for typical DP textbook problems.
    // 105 is safe to prevent out-of-bounds for standard inputs.
    double p[105]; // Probabilities of successful searches
    double q[105]; // Probabilities of unsuccessful searches
    
    // DP tables: 
    // e[i][j] stores the minimum expected cost of searching keys i to j.
    // w[i][j] stores the sum of probabilities for keys i to j and dummies i-1 to j.
    double e[105][105]; 
    double w[105][105];
    
    printf("Enter number of distinct keys (n): ");
    scanf("%d", &n);
    
    printf("Enter the %d successful search probabilities (p1 to pn): ", n);
    for(int i = 1; i <= n; i++) {
        scanf("%lf", &p[i]);
    }
    
    printf("Enter the %d unsuccessful search probabilities (q0 to qn): ", n + 1);
    for(int i = 0; i <= n; i++) {
        scanf("%lf", &q[i]);
    }
    
    // Base cases: when the BST only contains dummy keys (length 0 sequences)
    for(int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }
    
    // Fill the DP table diagonally, where 'len' is the number of keys in the current tree
    for(int len = 1; len <= n; len++) {
        for(int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            
            // Initializing to a very large number before finding the minimum
            e[i][j] = DBL_MAX; 
            
            // The total probability weight for this sequence of keys
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            
            // Try making every key in this range the root of the tree
            for(int r = i; r <= j; r++) {
                // Cost = cost of left subtree + cost of right subtree + weight of current tree
                double current_cost = e[i][r - 1] + e[r + 1][j] + w[i][j];
                
                if(current_cost < e[i][j]) {
                    e[i][j] = current_cost;
                }
            }
        }
    }
    
    printf("\nMinimum Expected Search Cost: %.4lf\n", e[1][n]);
    
    return 0;
}