set terminal pdfcairo enhanced color font "Times,12" size 6in,4in
set output "mc_quasi.pdf"

set logscale xy
set xlabel "N"
set ylabel "error"
set title "Pseudo-random vs quasi-random Monte Carlo"

plot "mc_quasi.dat" using 1:5 with linespoints title "LCG actual", \
     "mc_quasi.dat" using 1:6 with linespoints title "mt19937 actual", \
     "mc_quasi.dat" using 1:7 with linespoints title "Quasi actual"