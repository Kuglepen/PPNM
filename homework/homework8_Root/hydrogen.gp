set terminal pdfcairo enhanced color font "Times,12" size 6in,4in
set output "hydrogen.pdf"

set xlabel "r"
set ylabel "f(r)"
set title "Hydrogen ground state"

plot "hydrogen.dat" using 1:2 with lines lw 2 title "numerical", \
     "hydrogen.dat" using 1:3 with lines lw 2 dt 2 title "exact"