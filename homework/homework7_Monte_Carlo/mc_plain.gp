set terminal pdfcairo enhanced color font "Times,12"
set output "mcplot.pdf"

set logscale xy
set xlabel "N"
set ylabel "error"
set title "Monte Carlo error scaling"

f(x) = 1/sqrt(x)

plot "mc_plain.dat" using 1:2 with lines lw 2 title "estimated", \
     "mc_plain.dat" using 1:3 with lines lw 2 title "actual", \
     f(x) with lines lw 2 dt 2 title "1/sqrt(N)"
