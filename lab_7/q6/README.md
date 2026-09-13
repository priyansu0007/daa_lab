# The Best Time to be Alive

## 1. Problem Statement
An editor of *The History of the World Science* wants to find the year when the largest number of prominent scientists were alive simultaneously. The input is the book's index, which contains the birth and death years of each scientist. An important rule is provided for edge cases: if person A died the same year person B was born, the death event is considered to have happened *before* the birth event. The objective is to devise an algorithm to find this optimal year and determine its complexity.

## 2. Approach
This problem can be elegantly solved using a **Line Sweep (or Event Processing) Algorithm**. 
Instead of looking at each scientist's lifespan as an interval and comparing all intervals (which would be inefficient), we break down each lifespan into two distinct events:
1. A **Birth** event, which adds 1 to the count of currently living scientists. Let's represent this as `+1`.
2. A **Death** event, which subtracts 1 from the count. Let's represent this as `-1`.

For $n$ scientists, we will have $2n$ events. We collect all these events and sort them chronologically by year. 
To handle the edge case (death happening before birth in the same year), we configure our sorting logic so that if two events share the same year, the `-1` (death) event is placed before the `+1` (birth) event.

After sorting, we perform a single linear sweep through the events, maintaining a running sum of alive scientists. We track the maximum value this sum reaches and record the year it happened.

## 3. Algorithm/ Pseudocode
```text
Algorithm BEST_TIME_TO_BE_ALIVE(births, deaths, n)
// Input: Arrays of birth years and death years for n scientists
// Output: The year with the maximum number of overlapping lives

START
    1. CREATE an array 'events' of size 2 * n.
    2. FOR i = 0 TO n - 1 DO:
           events[2*i]     = {year: births[i], type: +1}
           events[2*i + 1] = {year: deaths[i], type: -1}
           
    3. SORT 'events' using a custom comparator:
           Primary criteria: Sort by 'year' in ascending order.
           Secondary criteria: If years are equal, sort by 'type' in ascending order 
                               (so -1 comes before +1).
                               
    4. max_alive = 0
    5. current_alive = 0
    6. best_year = 0
    
    7. FOR EACH event IN events DO:
           current_alive = current_alive + event.type
           IF current_alive > max_alive THEN:
               max_alive = current_alive
               best_year = event.year
               
    8. PRINT best_year, max_alive
END
```

## 4. Complexity Analysis (Derived)

### i) Time Complexity
* **Derivation:** 
    1. Creating the `events` array requires iterating through the $n$ scientists, which takes $O(n)$ time.
    2. Sorting the $2n$ events using an efficient comparison-based sorting algorithm (like Quicksort or Merge Sort) takes $O(2n \log(2n))$, which simplifies to $O(n \log n)$.
    3. The final sweep iterates exactly once through the $2n$ sorted events, taking $O(2n) = O(n)$ time.
    Summing these up: $O(n) + O(n \log n) + O(n)$. The sorting step dominates the runtime.
* **Result:** **O(n log n)**.

### ii) Space Complexity
* **Derivation:** We create a new array `events` to store $2n$ event objects (each containing a year and a type). The space scales linearly with the number of input scientists. The sorting algorithm may also require $O(\log n)$ or $O(n)$ auxiliary stack space, but the structural allocation of $2n$ events dominates.
* **Result:** **O(n)** (Linear Space Complexity).

## 5. Sample Output
Suppose we have 3 scientists with the following lifespans:
* Scientist 1: 1800 - 1850
* Scientist 2: 1810 - 1840
* Scientist 3: 1820 - 1830

Running the algorithm translates this into sorted events:
(1800, +1), (1810, +1), (1820, +1), (1830, -1), (1840, -1), (1850, -1).
The running sum peaks at 3 after processing the event in 1820.

```text
Best year to be alive: 1820 with 3 scientists.
```
*(Explanation: In 1820, Scientist 1 (age 20), Scientist 2 (age 10), and Scientist 3 (just born) are all alive simultaneously, yielding the maximum overlap.)*
