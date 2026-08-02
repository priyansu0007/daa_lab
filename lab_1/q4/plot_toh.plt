# Save this file as plot_toh.plt

set terminal pngcairo size 800,600 background '#1e1e2e' font "Arial,12"
set output 'toh_moves.png'

set title "Towers of Hanoi: Moves vs Number of Discs" textcolor rgb "#cdd6f4" font ",14"
set xlabel "Number of Discs (N)" textcolor rgb "#cdd6f4"
set ylabel "Total Moves" textcolor rgb "#cdd6f4"

set border lc rgb "#585b70"
set key textcolor rgb "#cdd6f4" top left box lc rgb "#585b70"
set grid lc rgb "#313244"

# Set Y-axis to logarithmic scale to clearly see the exponential nature (optional, but helpful)
# set logscale y 2 

# Vibrant purple line for the plot
set style line 1 lc rgb "#cba6f7" lw 2 pt 7 ps 1.2   

plot "toh_data.dat" using 1:2 with linespoints ls 1 title "Moves T(n)"