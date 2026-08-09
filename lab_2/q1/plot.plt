# Output setup
set terminal pngcairo size 1800,900 enhanced font "Arial,11"
set output 'q1_plot_results_gnuplot.png'

# Read CSV format & handle missing filtered values seamlessly
set datafile separator ","
set datafile missing NaN
set key inside top left font ",9" spacing 1.2
set grid linestyle 1 linetype 0 linewidth 1 lc rgb "#cccccc"

# Define colors and markers
set style line 1 lc rgb "#1f77b4" pt 7 ps 1.5 lw 2  # Unsorted Array
set style line 2 lc rgb "#ff7f0e" pt 5 ps 1.5 lw 2  # Sorted Array
set style line 3 lc rgb "#2ca02c" pt 9 ps 1.5 lw 2  # SLL Unsorted
set style line 4 lc rgb "#d62728" pt 13 ps 1.5 lw 2 # SLL Sorted
set style line 5 lc rgb "#9467bd" pt 11 ps 1.5 lw 2 # DLL Unsorted
set style line 6 lc rgb "#8c564b" pt 15 ps 1.5 lw 2 # DLL Sorted

# Common labels
set xlabel "Number of Elements (N)"
set ylabel "Execution Time (seconds)"

# Setup multiplot grid (2 rows x 4 cols)
set multiplot layout 2,4 title "Order of Growth: Data Structure Operations" font ",16" offset 0,0.5

# Correct function to filter rows (returns NaN instead of 1/0 to allow unbroken line connection)
filter(col, ds) = (strcol(2) eq ds) ? column(col) : NaN

# ---------------------------------------------------------
# Plot 1: Insertion (Column 3)
# ---------------------------------------------------------
set title "Insertion Time" font ",12,bold"
plot 'results.csv' using 1:(filter(3, "Unsorted_Array")) smooth path title "Unsorted Array - O(1)" w lp ls 1, \
     '' using 1:(filter(3, "Sorted_Array"))   smooth path title "Sorted Array - O(N)" w lp ls 2, \
     '' using 1:(filter(3, "SLL_Unsorted"))   smooth path title "SLL Unsorted - O(1)" w lp ls 3, \
     '' using 1:(filter(3, "SLL_Sorted"))     smooth path title "SLL Sorted - O(N)" w lp ls 4, \
     '' using 1:(filter(3, "DLL_Unsorted"))   smooth path title "DLL Unsorted - O(1)" w lp ls 5, \
     '' using 1:(filter(3, "DLL_Sorted"))     smooth path title "DLL Sorted - O(N)" w lp ls 6

# ---------------------------------------------------------
# Plot 2: Search (Column 4)
# ---------------------------------------------------------
set title "Search Time" font ",12,bold"
plot 'results.csv' using 1:(filter(4, "Unsorted_Array")) smooth path title "Unsorted Array - O(N)" w lp ls 1, \
     '' using 1:(filter(4, "Sorted_Array"))   smooth path title "Sorted Array - O(log N)" w lp ls 2, \
     '' using 1:(filter(4, "SLL_Unsorted"))   smooth path title "SLL Unsorted - O(N)" w lp ls 3, \
     '' using 1:(filter(4, "SLL_Sorted"))     smooth path title "SLL Sorted - O(N)" w lp ls 4, \
     '' using 1:(filter(4, "DLL_Unsorted"))   smooth path title "DLL Unsorted - O(N)" w lp ls 5, \
     '' using 1:(filter(4, "DLL_Sorted"))     smooth path title "DLL Sorted - O(N)" w lp ls 6

# ---------------------------------------------------------
# Plot 3: Maximum (Column 5)
# ---------------------------------------------------------
set title "Maximum Time" font ",12,bold"
plot 'results.csv' using 1:(filter(5, "Unsorted_Array")) smooth path title "Unsorted Array - O(N)" w lp ls 1, \
     '' using 1:(filter(5, "Sorted_Array"))   smooth path title "Sorted Array - O(1)" w lp ls 2, \
     '' using 1:(filter(5, "SLL_Unsorted"))   smooth path title "SLL Unsorted - O(N)" w lp ls 3, \
     '' using 1:(filter(5, "SLL_Sorted"))     smooth path title "SLL Sorted - O(N)" w lp ls 4, \
     '' using 1:(filter(5, "DLL_Unsorted"))   smooth path title "DLL Unsorted - O(N)" w lp ls 5, \
     '' using 1:(filter(5, "DLL_Sorted"))     smooth path title "DLL Sorted - O(1)" w lp ls 6

# ---------------------------------------------------------
# Plot 4: Minimum (Column 6)
# ---------------------------------------------------------
set title "Minimum Time" font ",12,bold"
plot 'results.csv' using 1:(filter(6, "Unsorted_Array")) smooth path title "Unsorted Array - O(N)" w lp ls 1, \
     '' using 1:(filter(6, "Sorted_Array"))   smooth path title "Sorted Array - O(1)" w lp ls 2, \
     '' using 1:(filter(6, "SLL_Unsorted"))   smooth path title "SLL Unsorted - O(N)" w lp ls 3, \
     '' using 1:(filter(6, "SLL_Sorted"))     smooth path title "SLL Sorted - O(1)" w lp ls 4, \
     '' using 1:(filter(6, "DLL_Unsorted"))   smooth path title "DLL Unsorted - O(N)" w lp ls 5, \
     '' using 1:(filter(6, "DLL_Sorted"))     smooth path title "DLL Sorted - O(1)" w lp ls 6

# ---------------------------------------------------------
# Plot 5: Predecessor (Column 7)
# ---------------------------------------------------------
set title "Predecessor Time" font ",12,bold"
plot 'results.csv' using 1:(filter(7, "Unsorted_Array")) smooth path title "Unsorted Array - O(N)" w lp ls 1, \
     '' using 1:(filter(7, "Sorted_Array"))   smooth path title "Sorted Array - O(1)" w lp ls 2, \
     '' using 1:(filter(7, "SLL_Unsorted"))   smooth path title "SLL Unsorted - O(N)" w lp ls 3, \
     '' using 1:(filter(7, "SLL_Sorted"))     smooth path title "SLL Sorted - O(N)" w lp ls 4, \
     '' using 1:(filter(7, "DLL_Unsorted"))   smooth path title "DLL Unsorted - O(N)" w lp ls 5, \
     '' using 1:(filter(7, "DLL_Sorted"))     smooth path title "DLL Sorted - O(1)" w lp ls 6

# ---------------------------------------------------------
# Plot 6: Successor (Column 8)
# ---------------------------------------------------------
set title "Successor Time" font ",12,bold"
plot 'results.csv' using 1:(filter(8, "Unsorted_Array")) smooth path title "Unsorted Array - O(N)" w lp ls 1, \
     '' using 1:(filter(8, "Sorted_Array"))   smooth path title "Sorted Array - O(1)" w lp ls 2, \
     '' using 1:(filter(8, "SLL_Unsorted"))   smooth path title "SLL Unsorted - O(N)" w lp ls 3, \
     '' using 1:(filter(8, "SLL_Sorted"))     smooth path title "SLL Sorted - O(1)" w lp ls 4, \
     '' using 1:(filter(8, "DLL_Unsorted"))   smooth path title "DLL Unsorted - O(N)" w lp ls 5, \
     '' using 1:(filter(8, "DLL_Sorted"))     smooth path title "DLL Sorted - O(1)" w lp ls 6

# ---------------------------------------------------------
# Plot 7: Deletion (Column 9)
# ---------------------------------------------------------
set title "Deletion Time" font ",12,bold"
plot 'results.csv' using 1:(filter(9, "Unsorted_Array")) smooth path title "Unsorted Array - O(1)" w lp ls 1, \
     '' using 1:(filter(9, "Sorted_Array"))   smooth path title "Sorted Array - O(N)" w lp ls 2, \
     '' using 1:(filter(9, "SLL_Unsorted"))   smooth path title "SLL Unsorted - O(N)" w lp ls 3, \
     '' using 1:(filter(9, "SLL_Sorted"))     smooth path title "SLL Sorted - O(N)" w lp ls 4, \
     '' using 1:(filter(9, "DLL_Unsorted"))   smooth path title "DLL Unsorted - O(1)" w lp ls 5, \
     '' using 1:(filter(9, "DLL_Sorted"))     smooth path title "DLL Sorted - O(1)" w lp ls 6

unset multiplot