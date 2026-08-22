# Peak Party Time Finder

## Overview
This program calculates the maximum number of people present at a party simultaneously and identifies the exact time this peak occurred. It processes a list of entry and exit times for `n` individuals to find the overlapping intervals efficiently.

## Approach
To avoid a brute-force approach that checks every possible time interval (which would be inefficient), the algorithm uses a **Sorting and Two-Pointer (Line Sweep) approach**:
1. **Separation and Sorting:** The entry and exit times are separated into two distinct arrays. Both arrays are then sorted in ascending order. This effectively creates a chronological timeline of "events" (arrivals and departures) without needing to keep the individual entry/exit pairs linked.
2. **Two-Pointer Traversal:** We use two pointers to sweep through the sorted entry and exit times. 
   - If the next event is an entry (i.e., the current entry time is strictly less than the current exit time), the number of people currently at the party increases.
   - If the next event is an exit, the number of people decreases.
3. **Peak Tracking:** Throughout this traversal, we continuously update the maximum number of people recorded and the time it happened.

## Algorithm
1. Read the number of people, `n`.
2. Dynamically allocate two arrays of size `n`: `entry` and `exit`.
3. Read the entry and exit times for each person, ensuring that the entry time is strictly less than the exit time.
4. Sort the `entry` array in ascending order using QuickSort (`qsort`).
5. Sort the `exit` array in ascending order using QuickSort (`qsort`).
6. Initialize two pointers, `i = 0` (for entries) and `j = 0` (for exits). Initialize `current_people`, `max_people`, and `time_of_max` to `0`.
7. Loop while `i < n` and `j < n`:
   * If `entry[i] < exit[j]`: Increment `current_people`. If `current_people` is greater than `max_people`, update `max_people` and set `time_of_max` to `entry[i]`. Increment pointer `i`.
   * Else: Decrement `current_people` and increment pointer `j`.
8. Print `max_people` and `time_of_max`.
9. Free the dynamically allocated memory.

## Pseudocode
```text
function findPeakPartyTime(entry, exit, n):
    sort(entry)
    sort(exit)

    current_people = 0
    max_people = 0
    time_of_max = 0
    
    i = 0
    j = 0
    
    while i < n and j < n:
        if entry[i] < exit[j]:
            current_people = current_people + 1
            if current_people > max_people:
                max_people = current_people
                time_of_max = entry[i]
            i = i + 1
        else:
            current_people = current_people - 1
            j = j + 1
            
    print("Maximum people: " + max_people)
    print("Peak time: " + time_of_max)
```

## Complexity Analysis
* **Time Complexity:** $O(n \log n)$
  * Sorting the `entry` and `exit` arrays takes $O(n \log n)$ time. The two-pointer traversal takes $O(n)$ time since each pointer moves at most `n` times. The dominating factor is the sorting step, making the overall time complexity $O(n \log n)$.
* **Space Complexity:** $O(n)$ total, $O(1)$ auxiliary
  * Storing the `entry` and `exit` times requires $O(n)$ space. Aside from the memory allocated for the inputs and the call stack used by `qsort` (which takes $O(\log n)$), the algorithm uses only a few variables for pointers and counters, resulting in an auxiliary space complexity of $O(1)$.

## Sample Output
```text
Enter the total number of people (n): 5
Enter the entry and exit times for each person (ai bi):
Person 1: 1 4
Person 2: 2 5
Person 3: 9 12
Person 4: 5 9
Person 5: 5 12

Analysis Complete:
Maximum people present simultaneously: 3
Time when the party peaked: 5
```
