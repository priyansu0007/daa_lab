# Question 7: Rod Cutting with Reconstruction

## 1. Problem Statement
Given a rod of length $n$ inches and an array of prices $P = [p_1, p_2, \dots, p_n]$, where $p_i$ denotes the market price of a rod piece of length $i$ inches, determine:
1. The maximum revenue obtainable by cutting up the rod and selling the pieces.
2. The exact lengths of the pieces that constitute the optimal decomposition (reconstruction).

Cuts are integral and can be made in any combination (including leaving the rod uncut), and the sum of the piece lengths must equal $n$. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

## 2. Approach
This is an optimization problem that can be efficiently solved using **Dynamic Programming (DP)**. We use a bottom-up approach to calculate the maximum revenue for smaller rod lengths and use those results to build up to the full length $n$.

1. **State Definition:** We use a 1D array `dp`, where `dp[i]` stores the maximum revenue obtainable from a rod of length $i$. 
2. **Base Case:** A rod of length 0 yields a revenue of 0, so `dp[0] = 0`.
3. **Recurrence Relation:** For a rod of length $i$, we can try making a first cut of length $j$ (where $1 \le j \le i$). The revenue for this cut is the price of piece $j$ plus the optimal revenue for the remaining rod of length $i - j$. We take the maximum across all possible first cuts $j$:
   $$dp[i] = \max_{1 \le j \le i} ( price[j] + dp[i-j] )$$
4. **Reconstruction:** To reconstruct the solution, we maintain a second array, `first_cut`. Whenever we find a new maximum for `dp[i]` using a cut of length $j$, we store `first_cut[i] = j`. After the DP table is fully computed, we can trace back the exact cuts by starting at length $n$, printing `first_cut[n]`, and reducing the remaining length by that amount until the length reaches 0.

## 3. Algorithm
1. Read the length of the rod $n$.
2. Read the price array `price` where `price[i]` corresponds to the price of a piece of length $i$. (Using 1-based indexing).
3. Initialize the `dp` array of size $n+1$ with 0.
4. Initialize the `first_cut` array of size $n+1$ with 0.
5. Iterate `i` from $1$ to $n$ (computing max revenue for each length up to $n$):
   - Set `max_val = -1`
   - Iterate `j` from $1$ to $i$ (trying every possible first cut size $j$):
     - If `price[j] + dp[i-j] > max_val`:
       - Update `max_val = price[j] + dp[i-j]`
       - Record this optimal cut: `first_cut[i] = j`
   - Store the computed maximum: `dp[i] = max_val`
6. Output `dp[n]` as the maximum revenue.
7. To reconstruct the cuts, set `curr_length = n`.
8. While `curr_length > 0`:
   - Print `first_cut[curr_length]`
   - Update `curr_length = curr_length - first_cut[curr_length]`

## 4. Pseudocode
```text
function rod_cutting(n, price):
    create array dp of size n+1
    create array first_cut of size n+1
    
    dp[0] = 0
    
    for i from 1 to n:
        max_val = -1
        for j from 1 to i:
            if price[j] + dp[i-j] > max_val:
                max_val = price[j] + dp[i-j]
                first_cut[i] = j
        dp[i] = max_val
        
    print "Maximum Revenue: ", dp[n]
    
    print "Optimal piece lengths: "
    curr_length = n
    while curr_length > 0:
        print first_cut[curr_length]
        curr_length = curr_length - first_cut[curr_length]
```

## 5. Complexity Analysis

### Time Complexity Derivation
The total time complexity consists of the time taken to fill the DP array and the time taken for the reconstruction traceback.

1. **DP Table Construction:** We have an outer loop running $n$ times (for $i = 1$ to $n$) and an inner loop running $i$ times (for $j = 1$ to $i$). The operation inside the inner loop is basic arithmetic and comparison, which takes $O(1)$ time. The total number of iterations is the sum of the first $n$ natural numbers:
   $$\text{Total iterations} = \sum_{i=1}^{n} \sum_{j=1}^{i} 1 = \sum_{i=1}^{n} i = \frac{n(n+1)}{2} = \frac{n^2}{2} + \frac{n}{2}$$
   Dropping the constants and lower-order terms, this yields $O(n^2)$.
2. **Reconstruction:** The while loop subtracts at least 1 from `curr_length` in every iteration. In the worst case (where the rod is cut into $n$ pieces of length 1), the loop runs $n$ times. Thus, reconstruction takes $O(n)$ time.

Total Time Complexity:
$$O(n^2) + O(n) = O(n^2)$$

### Space Complexity Derivation
The total space complexity depends on the auxiliary data structures allocated.

1. **DP Array:** We allocate an array of size $n+1$ to store the maximum revenue for each sub-length.
2. **First Cut Array:** We allocate another array of size $n+1$ to store the trace-back indices.
   
Total Space Required:
$$\text{Total Elements} = (n + 1) + (n + 1) = 2n + 2$$

Dropping constants, the auxiliary space scales linearly with $n$.
Total Space Complexity:
$$O(n)$$

## 6. Sample Outputs

**Test Case 1: Standard Cuts**
```text
Enter the length of the rod (n): 8
Enter the prices for pieces of length 1 to 8:
1 5 8 9 10 17 17 20

Maximum Revenue: 22
Optimal piece lengths: 2 6 
```
*(Explanation: The optimal way is to cut the rod into pieces of length 2 (price 5) and 6 (price 17), giving a total of 22.)*

**Test Case 2: No Cuts Needed**
```text
Enter the length of the rod (n): 4
Enter the prices for pieces of length 1 to 4:
1 5 8 20

Maximum Revenue: 20
Optimal piece lengths: 4 
```
*(Explanation: The price for a whole rod of length 4 is 20, which is strictly better than any combination of smaller cuts.)*