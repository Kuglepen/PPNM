set terminal pdfcairo size 8,6
set output "plot.pdf"

set grid
set key center top
set xlabel "x"
set ylabel "y"

set multiplot layout 2,1

set title "Linear vs Quadratic spline"
plot "data.txt" using 1:2 with lines lw 2 title "linear", \
     "data.txt" using 1:3 with lines lw 2 title "quadratic", \
     "data_points.txt" using 1:2 with points pt 7 ps 1.2 title "data points"

set title "Integrals"
plot "data.txt" using 1:4 with lines lw 2 title "linear integ", \
     "data.txt" using 1:5 with lines lw 2 title "quadratic integ"

unset multiplot