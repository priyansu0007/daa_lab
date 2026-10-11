# Minimise Deviation in Array

## 1. Problem Statement

You are given an array of positive integers. You can perform two types of operations on the elements of the array any number of times:
1. If an element is **odd**, you can multiply it by 2.
2. If an element is **even**, you can divide it by 2.

The **deviation** of the array is defined as the difference between the maximum and minimum elements in the array: $(\max(A) - \min(A))$. Your goal is to find the minimum possible deviation of the array after applying any number of these operations.

## 2. Approach

The problem involves two opposing operations (multiplying and dividing), which makes the state space complex. To simplify this, we can use a **Two-Way Greedy Approach** powered by a **Max-Heap** to transform the problem into a one-way reduction path.

* **Normalization:** We first eliminate the multiplication operation entirely. We do this by iterating through the array and multiplying every odd number by 2. Now, all elements in the array are even. This forces every element to its absolute maximum possible value in the state space. We also track the global minimum value of this newly normalized array.
* **Greedy Reduction:** We insert all elements into a Max-Heap. The current deviation is the difference between the top of the heap (the maximum element) and our tracked global minimum. To reduce the deviation, our only option is to decrease the maximum element. We pop the max element, divide it by 2, update our global minimum if necessary, and push it back into the heap. We record the smallest deviation seen so far.
* **Termination:** We continue this halving process until the maximum element extracted from the heap is odd. Once it is odd, it can no longer be divided by 2, meaning we cannot reduce the upper bound any further. At this point, the process is complete.

## 3. Algorithm

1. **Initialize Data Structures:** Create an empty Max-Heap and variables to track the `global_min` and `min_deviation`. Set both to infinity initially.

2. **Normalize the Array:** Loop through each element in the input array.
   * If the element is odd, multiply it by 2.
   * Push the resulting element into the Max-Heap.
   * Update `global_min` to be the minimum of its current value and this element.

3. **Greedy Reduction Loop:** While the top element of the Max-Heap is even:
   * Pop the top element (`max_val`) from the Max-Heap.
   * Calculate the current deviation: `max_val - global_min`. Update `min_deviation` if this is smaller than the current `min_deviation`.
   * Divide `max_val` by 2.
   * Update `global_min` to be the minimum of its current value and the new `max_val`.
   * Push the new `max_val` back into the Max-Heap.

4. **Final Check:** When the loop terminates (because the top element is odd), do one final check to update `min_deviation` using the top element of the heap and the `global_min`.

5. **Return:** Output the `min_deviation`.

## 4. Pseudocode

```
function minimum_deviation(nums):
    if nums.length <= 1:
        return 0
        
    max_heap = new MaxHeap()
    global_min = INFINITY
    
    // Step 2: Normalize array and find initial minimum
    for val in nums:
        if val % 2 != 0:
            val = val * 2
            
        max_heap.push(val)
        global_min = min(global_min, val)
        
    min_deviation = INFINITY
    
    // Step 3: Greedy reduction
    while true:
        max_val = max_heap.pop()
        
        // Update the minimum deviation found so far
        current_deviation = max_val - global_min
        min_deviation = min(min_deviation, current_deviation)
        
        // Step 4: Terminate if the maximum element is odd
        if max_val % 2 != 0:
            break
            
        // Divide by 2, update global minimum, and push back
        max_val = max_val / 2
        global_min = min(global_min, max_val)
        max_heap.push(max_val)
        
    return min_deviation

```

## 5. Complexity Analysis

* **Time Complexity:** 
  * Normalizing the array and building the initial heap takes $O(N \log N)$ time, where $N$ is the number of elements in the array.
  * Let $M$ be the maximum possible value in the normalized array. An even number can be divided by 2 at most $O(\log M)$ times before it becomes odd. Since there are $N$ elements, the maximum number of extractions and insertions the loop will perform is $O(N \log M)$.
  * Each heap operation inside the loop takes $O(\log N)$ time.
  * **Overall Time Complexity:** $O(N \log M \log N)$, where $M$ is the maximum value in the array.
* **Space Complexity:** 
  * The algorithm dynamically allocates a Max-Heap that stores exactly $N$ elements.
  * **Overall Space Complexity:** $O(N)$, which scales strictly linearly with the number of input items.

## 6. Sample Output

```
Array: [1, 2, 3, 4]
Minimum Deviation: 1
(Transform to [2, 2, 3, 2], max=3, min=2, diff=1)

Array: [4, 1, 5, 20, 3]
Minimum Deviation: 3
(Transform to [4, 2, 5, 5, 6], max=6, min=2 -> divide 6 -> max=5, min=2 -> divide 4 -> max=5, min=2. diff=3)

```