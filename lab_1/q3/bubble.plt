# Set output settings
set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'bubble_sort_comparison.png'

# Titles and Labels
set title "Performance Analysis of Bubble Sort (Randomised Data Sequences)" font "Arial,14"
set xlabel "Array Size (n)" font "Arial,12"
set ylabel "Number of Comparisons" font "Arial,12"

# Grid and Legend
set grid
set key left top box opaque

# Plot data
# Unoptimized will show a massive O(N^2) curve
# Optimized will stay near the bottom, showing near O(N) efficiency due to early termination
plot 'bubble_data.dat' using 1:2 with linespoints lc rgb "red" lw 2 pt 7 title 'Algorithm (ii): Always Completes Pass', \
     'bubble_data.dat' using 1:3 with linespoints lc rgb "green" lw 2 pt 7 title 'Algorithm (i): Terminates Early'