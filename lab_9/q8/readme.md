# Minimum Number of Meeting Rooms

## 1. Problem Statement

Given an array of meeting time intervals where each interval consists of a start time and an end time `[start, end]`, determine the minimum number of conference rooms required to schedule all the meetings without any overlap in a single room.

## 2. Approach

To find the minimum number of rooms needed, we must determine the maximum number of overlapping meetings at any single point in time. This is effectively a chronological timeline simulation.

Instead of treating each meeting as an indivisible block, we can decouple the start times from the end times. We extract all start times into one list and all end times into another, then sort both lists in ascending order. Using a **Two-Pointer Chronological Sweep**, we walk through the timeline. If the next earliest event is a meeting starting, we need an additional room. If the next earliest event is a meeting ending, a room frees up. By tracking the active number of rooms during this sweep, the peak value reached is the minimum number of distinct rooms required.

## 3. Algorithm

1. **Extract Times:** Create two separate arrays of size $N$: one for all `start` times and one for all `end` times.

2. **Sort:** Sort both the `starts` array and the `ends` array in ascending chronological order.

3. **Initialize Pointers:** Set two pointers, `s_ptr = 0` (for the starts array) and `e_ptr = 0` (for the ends array). Initialize `active_rooms = 0` and `max_rooms = 0`.

4. **Timeline Traversal:** While `s_ptr` is less than the total number of meetings $N$:

   * **Meeting Starts:** If `starts[s_ptr] < ends[e_ptr]`, a new meeting is beginning before the earliest concluding meeting has finished. Increment `active_rooms`, update `max_rooms` to be the maximum of its current value and `active_rooms`, and increment `s_ptr`.
   
   * **Meeting Ends:** Otherwise (`starts[s_ptr] >= ends[e_ptr]`), a meeting has concluded and freed up a room. Decrement `active_rooms` and increment `e_ptr`.

5. **Return:** After traversing all start times, `max_rooms` holds the absolute minimum number of rooms required.

## 4. Pseudocode

```
function min_meeting_rooms(intervals):
    n = intervals.length
    if n == 0:
        return 0
        
    // Step 1: Extract start and end times
    starts = array of size n
    ends = array of size n
    for i from 0 to n - 1:
        starts[i] = intervals[i].start
        ends[i] = intervals[i].end
        
    // Step 2: Sort chronologically
    sort(starts)
    sort(ends)
    
    // Step 3: Initialize tracking variables
    active_rooms = 0
    max_rooms = 0
    s_ptr = 0
    e_ptr = 0
    
    // Step 4: Two-pointer sweep
    while s_ptr < n:
        if starts[s_ptr] < ends[e_ptr]:
            // A meeting started, we need a room
            active_rooms += 1
            max_rooms = max(max_rooms, active_rooms)
            s_ptr += 1
        else:
            // A meeting ended, a room is freed
            active_rooms -= 1
            e_ptr += 1
            
    return max_rooms
```

## 5. Complexity Analysis

* **Time Complexity:**

  * Extracting the start and end times takes $O(N)$.
  
  * Sorting the `starts` and `ends` arrays takes $O(N \log N)$ time.
  
  * The timeline traversal (`while` loop) iterates exactly $N$ times, taking $O(N)$ operations.
  
  * **Overall Time Complexity:** $O(N \log N)$, as the sorting phase acts as the bounding bottleneck.

* **Space Complexity:**

  * The algorithm provisions two auxiliary $N$-length arrays (`starts` and `ends`) to store the decoupled timestamps.
  
  * **Overall Space Complexity:** $O(N)$, requiring memory strictly linear to the number of input intervals.

## 6. Sample Output

```
Intervals: [[0, 30], [5, 10], [15, 20]]
Minimum meeting rooms: 2

Intervals: [[7, 10], [2, 4]]
Minimum meeting rooms: 1

Intervals: [[1, 5], [5, 9], [9, 12]]
Minimum meeting rooms: 1
```