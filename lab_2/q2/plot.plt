# Set the output format to PNG and define the file name
set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output 'merge_comparison.png'

# Add titles and labels
set title "Time Complexity: 2-Way vs 3-Way Merge Sort"
set xlabel "Array Size (n)"
set ylabel "Execution Time (Seconds)"

# Enable a grid for better readability
set grid

# Position the legend/key
set key top left box

# Plot the data from merge.dat
# column 1 is X, column 2 is Y for 2-way, column 3 is Y for 3-way
plot "merge.dat" using 1:2 with linespoints lw 2 pt 7 title "2-Way Merge Sort", \
     "merge.dat" using 1:3 with linespoints lw 2 pt 5 title "3-Way Merge Sort"