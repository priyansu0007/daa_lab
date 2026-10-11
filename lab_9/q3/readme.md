# Minimum Refueling Stops (Reverse Greedy)

## 1. Problem Statement

A vehicle needs to reach a target destination at distance $D$ starting with an initial fuel amount $F$. Along the route, there are $n$ gas stations, each represented by a pair $(d_i, f_i)$ indicating its distance from the origin and the amount of fuel it can provide. Assuming the vehicle consumes one unit of fuel per unit of distance, find the minimum number of refueling stops required to reach the target. If it is impossible to reach the target, return -1.

## 2. Approach

The optimal way to minimize stops is to use a **"Lazy Greedy"** strategy supported by a Max-Priority Queue (Max-Heap). 

Instead of deciding to stop at a gas station when we arrive at it, we simply "remember" that we passed it. As we drive past a station, we add its fuel capacity to our Max-Heap. We keep driving until our vehicle completely runs out of fuel. At the exact moment our fuel drops below zero, we retroactively "stop" at the previously encountered station that offers the absolute maximum fuel. We do this by popping the largest value from our Max-Heap and adding it to our tank. By always choosing the largest available fuel boost only when absolutely necessary, we maximize the distance gained per stop, thereby strictly minimizing the total number of stops.

## 3. Algorithm

1. **Sort Stations:** Sort the array of gas stations in ascending order based on their distance from the starting point.
2. **Initialize:** Create an empty Max-Heap to track available fuel. Set `current_pos = 0`, `current_fuel = F`, and `stops = 0`.
3. **Iterate Route:** Treat the target $D$ as the final "station" with 0 fuel. Loop through all stations (including the target).
4. **Calculate Distance:** For each station, calculate the distance from the `current_pos` to the station's location.
5. **Retroactive Refueling:** While `current_fuel` is less than the distance needed to reach the next station:
   * If the Max-Heap is empty, it means we have exhausted all passed stations and still can't reach the next point. Return `-1` (unreachable).
   * Otherwise, pop the maximum fuel amount from the Max-Heap, add it to `current_fuel`, and increment the `stops` counter.
6. **Advance:** Subtract the distance covered from `current_fuel`, update `current_pos` to the station's distance, and push the current station's fuel capacity into the Max-Heap.
7. **Complete:** Once the loop successfully reaches the target distance, return the total `stops`.

## 4. Pseudocode

```
function min_refuel_stops(target, start_fuel, stations):
    // Step 1: Sort stations by distance
    sort(stations, key=lambda x: x.distance)
    
    max_heap = new MaxHeap()
    stops = 0
    current_fuel = start_fuel
    current_pos = 0
    
    // Step 3: Iterate through stations + target
    for i from 0 to stations.length:
        if i < stations.length:
            next_pos = stations[i].distance
        else:
            next_pos = target
            
        distance_to_cover = next_pos - current_pos
        
        // Step 5: Refuel if necessary
        while current_fuel < distance_to_cover:
            if max_heap.is_empty():
                return -1 // Unreachable
                
            current_fuel += max_heap.pop()
            stops += 1
            
        // Step 6: Advance and store station fuel
        current_fuel -= distance_to_cover
        current_pos = next_pos
        
        if i < stations.length:
            max_heap.push(stations[i].fuel)
            
    return stops
```

## 5. Complexity Analysis

* **Time Complexity:** 
  * Sorting the $N$ gas stations by distance takes $O(N \log N)$ time.
  * In the worst case, we push all $N$ stations into the Max-Heap, which takes $O(N \log N)$ time in total.
  * We also pop from the heap at most $N$ times, which takes $O(N \log N)$ time.
  * **Overall Time Complexity:** $O(N \log N)$, bounded primarily by the sorting and heap operations.

* **Space Complexity:** 
  * The algorithm dynamically allocates a Max-Heap structure. In the worst-case scenario (where we pass every gas station before needing to refuel), the heap will store all $N$ fuel values simultaneously.
  * **Overall Space Complexity:** $O(N)$, which scales strictly linearly with the number of input stations.

## 6. Sample Output

```
Intervals / Route Data:
Target Distance: 100
Starting Fuel: 10
Stations: [(10, 60), (20, 30), (30, 30), (60, 40)]

Minimum number of refueling stops required: 2
```