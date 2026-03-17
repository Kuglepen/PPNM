set terminal pdfcairo enhanced font "Times,12" size 10cm,7cm
set output 'fig_scaling.pdf'

set title "Scaling of Jacobi diagonalization"
set xlabel "N"
set ylabel "Time (s)"
set grid


plot "data_times.txt" using 1:2 with linespoints lw 2 pt 7 title "Measured"