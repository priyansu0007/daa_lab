# Reorganize String with K-Distance Apart

## 1. Problem Statement

Given a string $S$ and an integer $K$, rearrange the characters of $S$ such that any two identical characters are placed at least $K$ distance apart from each other. If it is impossible to construct such a string, return an empty string.

## 2. Approach

This problem is a classic scheduling task that can be optimally solved using a **Greedy Algorithm** paired with a **Max-Priority Queue (Max-Heap)** and a **Cooldown Queue**. 

To maximize the probability of successfully placing all characters without violating the $K$-distance constraint, we must prioritize placing the characters with the highest remaining frequency. We extract the most frequent available character from the Max-Heap, append it to our result, and decrement its frequency. Because this character cannot be used again for the next $K - 1$ steps, we place it into a temporary "cooldown" queue. Once a character has waited for $K$ steps, it is released from the cooldown queue and pushed back into the Max-Heap (provided its frequency is still greater than zero). If we ever need a character but the Max-Heap is empty, it means all remaining characters are stuck in cooldown, making the rearrangement impossible.

## 3. Algorithm

1. **Edge Case Check:** If $K \le 1$, any arrangement is valid, so simply return the original string $S$.
2. **Frequency Counting:** Iterate through the string $S$ and count the occurrences of each character.
3. **Initialize Max-Heap:** Insert all unique characters and their frequencies into a Max-Heap, ordered descendingly by frequency.
4. **Initialize Cooldown:** Create a cooldown array or queue of size $K$ to hold characters that are currently restricted.
5. **String Construction:** Loop $N$ times (where $N$ is the length of $S$):
   * Check if the character at the current cooldown index (i.e., `step % K`) is ready to be released. If its frequency is $> 0$, push it back into the Max-Heap.
   * If the Max-Heap is empty, return an empty string (impossible).
   * Pop the character with the highest frequency from the Max-Heap.
   * Append this character to the result string and decrement its frequency.
   * Place this updated character into the cooldown queue at the current index.
6. **Return Result:** Once the loop completes successfully, return the constructed string.

## 4. Pseudocode

```
function rearrange_string(S, K):
    if K <= 1:
        return S
        
    // Step 2: Count frequencies
    freq_map = new Map()
    for char in S:
        freq_map[char]++
        
    // Step 3: Initialize Max-Heap
    max_heap = new MaxHeap()
    for (char, count) in freq_map:
        max_heap.push( (char, count) )
        
    // Step 4: Initialize Cooldown Queue
    cooldown_queue = array of size K, filled with null
    result = ""
    
    // Step 5: Construct String
    for i from 0 to S.length - 1:
        queue_idx = i % K
        
        // Release character from cooldown
        if cooldown_queue[queue_idx] != null and cooldown_queue[queue_idx].count > 0:
            max_heap.push(cooldown_queue[queue_idx])
            
        // Check for impossibility
        if max_heap.is_empty():
            return ""
            
        // Greedily take most frequent character
        current = max_heap.pop()
        result += current.char
        current.count--
        
        // Put used character on cooldown
        cooldown_queue[queue_idx] = current
        
    return result
```

## 5. Complexity Analysis

* **Time Complexity:** 
  * Counting frequencies takes $O(N)$ time, where $N$ is the length of the string.
  * Pushing up to $\Sigma$ unique characters into the heap takes $O(\Sigma \log \Sigma)$, where $\Sigma \le 256$ for ASCII strings.
  * The main loop runs $N$ times. In each iteration, pushing and popping from the heap takes $O(\log \Sigma)$.
  * **Overall Time Complexity:** $O(N \log \Sigma)$. Since the alphabet size $\Sigma$ is a constant (e.g., 26 for lowercase English letters or 256 for ASCII), $\log \Sigma$ simplifies to $O(1)$. Thus, the strict asymptotic time complexity is **$O(N)$**.
* **Space Complexity:** 
  * The result string requires $O(N)$ space.
  * The Max-Heap stores at most $\Sigma$ elements, taking $O(\Sigma)$ space.
  * The Cooldown queue requires $O(K)$ space.
  * **Overall Space Complexity:** $O(N + K + \Sigma)$. Dropping the constant $\Sigma$, this evaluates to **$O(N + K)$**.

## 6. Sample Output

```
Input: "aabbcc", K=3
Output: "abcabc"

Input: "aaabc", K=3
Output: ""
(Impossible to separate 'a' by 3 positions)

Input: "aaadbbcc", K=2
Output: "abacabcd" 
```