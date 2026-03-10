set terminal pdfcairo size 10cm,7cm
set output "runtime_vs_threads.pdf"

set xlabel "Number of threads"
set ylabel "Runtime (seconds)"
set title "Runtime vs Threads for Harmonic Sum"

set grid

plot "times.dat" using 1:2 with linespoints lw 2 pt 7 title "runtime"