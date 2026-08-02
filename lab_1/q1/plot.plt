# Output settings
set terminal pngcairo size 1200,800 enhanced font 'Arial,11'
set output 'complexity.png'

# Titles and Labels
set title "Algorithmic Time Complexities (Log-Log Scale)" font ",16"
set xlabel "log_{10}(n)" font ",12"
set ylabel "log_{10}(f(n))" font ",12"

# Grid and Legend (Key)
set grid
set key outside right top box
set key title "Functions" font ",12"

# FIX: Restrict the Y-axis so 3^n doesn't squish everything else
set yrange [-2:60]

# Plotting the 12 functions
plot "data_loglog.txt" using 1:2  with lines lw 2 title "1/n", \
     "data_loglog.txt" using 1:3  with lines lw 2 title "log_2(n)", \
     "data_loglog.txt" using 1:4  with lines lw 2 title "12*sqrt(n)", \
     "data_loglog.txt" using 1:5  with lines lw 2 title "50*n^{0.5}", \
     "data_loglog.txt" using 1:6  with lines lw 2 title "n^{0.51}", \
     "data_loglog.txt" using 1:7  with lines lw 2 title "2^{32}*n", \
     "data_loglog.txt" using 1:8  with lines lw 2 title "n*log_2(n)", \
     "data_loglog.txt" using 1:9  with lines lw 2 title "n^2 - 324", \
     "data_loglog.txt" using 1:10 with lines lw 2 title "100n^2 + 6n", \
     "data_loglog.txt" using 1:11 with lines lw 2 title "2n^3", \
     "data_loglog.txt" using 1:12 with lines lw 2 title "n^{log_2(n)}", \
     "data_loglog.txt" using 1:13 with lines lw 2 title "3^n"