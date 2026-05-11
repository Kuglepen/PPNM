set terminal pdfcairo enhanced color font "Times,12" size 6in,4in
set output "wave_eps.pdf"

set title "Hydrogen wavefunction - varying eps"
set xlabel "r"
set ylabel "f(r)"

plot \
    "wave_eps.dat" index 0 using 1:2 with lines lw 2 title "eps = 10", \
    "wave_eps.dat" index 1 using 1:2 with lines lw 2 title "eps = 1", \
    "wave_eps.dat" index 2 using 1:2 with lines lw 2 title "eps = 1e-1", \
    "wave_eps.dat" index 3 using 1:2 with lines lw 2 title "eps = 1e-5", \
    "wave_rmax.dat" index 3 using 1:3 with lines lw 2 dt 2 lc rgb "black" title "exact"
