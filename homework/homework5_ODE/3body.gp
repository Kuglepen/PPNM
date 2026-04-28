set terminal pdfcairo enhanced color font "Times,12" size 6in,6in
set output "3body.pdf"

set title "Three-Body Figure-8 Orbit"
set xlabel "x"
set ylabel "y"

set size ratio -1
set grid
set key top right

plot "threebody.dat" using 2:3 with lines lw 2 title "body 1", \
     "threebody.dat" using 4:5 with lines lw 2 title "body 2", \
     "threebody.dat" using 6:7 with lines lw 2 title "body 3"