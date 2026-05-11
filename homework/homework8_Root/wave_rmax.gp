set terminal pdfcairo enhanced color font "Times,12" size 6in,4in
set output "wave_rmax.pdf"

set title "Hydrogen wavefunction - varying rmax"
set xlabel "r"
set ylabel "f(r)"

plot \
    "wave_rmax.dat" index 0 using 1:2 with lines lw 2 title "rmax = 1", \
    "wave_rmax.dat" index 1 using 1:2 with lines lw 2 title "rmax = 3", \
    "wave_rmax.dat" index 2 using 1:2 with lines lw 2 title "rmax = 5", \
    "wave_rmax.dat" index 3 using 1:2 with lines lw 2 title "rmax = 10", \
    "wave_rmax.dat" index 3 using 1:3 with lines lw 2 dt 2 lc rgb "black" title "exact"