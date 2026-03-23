set terminal pdfcairo enhanced font "Times,12" size 10cm,7cm
set output 'fig_rmax.pdf'

set xlabel "rmax"
set ylabel "E₀ (ground state energy)"
set title "Convergence vs rmax (Δr fixed)"
set grid
set key bottom right

plot "data_rmax.txt" using 1:2 with linespoints lw 2 pt 7 title "Numerical", \
     -0.5 with lines dt 2 lw 2 title "Exact (-0.5)"