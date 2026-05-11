set terminal pdfcairo enhanced color font "Times,12" size 6in,4in
set output "wave_rmin.pdf"

set title "Hydrogen wavefunction - varying rmin"
set xlabel "r"
set ylabel "f(r)"

plot \
    "wave_rmin.dat" index 0 using 1:2 with lines lw 2 title "rmin = 1e-5", \
    "wave_rmin.dat" index 1 using 1:2 with lines lw 2 title "rmin = 0.1", \
    "wave_rmin.dat" index 2 using 1:2 with lines lw 2 title "rmin = 0.2", \
    "wave_rmin.dat" index 3 using 1:2 with lines lw 2 title "rmin = 0.4", \
    "wave_rmax.dat" index 3 using 1:3 with lines lw 2 dt 2 lc rgb "black" title "exact"