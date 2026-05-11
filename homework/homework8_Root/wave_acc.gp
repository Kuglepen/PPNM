set terminal pdfcairo enhanced color font "Times,12" size 6in,4in
set output "wave_acc.pdf"

set title "Hydrogen wavefunction - varying acc"
set xlabel "r"
set ylabel "f(r)"

plot \
    "wave_acc.dat" index 0 using 1:2 with lines lw 2 title "acc = 10", \
    "wave_acc.dat" index 1 using 1:2 with lines lw 2 title "acc = 1", \
    "wave_acc.dat" index 2 using 1:2 with lines lw 2 title "acc = 1e-1", \
    "wave_acc.dat" index 3 using 1:2 with lines lw 2 title "acc = 1e-5", \
    "wave_rmax.dat" index 3 using 1:3 with lines lw 2 dt 2 lc rgb "black" title "exact"
