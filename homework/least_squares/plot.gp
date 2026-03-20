set terminal pdfcairo enhanced color font "Times-New-Roman,12" size 6in,4in
set output "fit.pdf"

set title "Radioactive decay of ThX"
set xlabel "Time (days)"
set ylabel "Activity"

set grid back lc rgb "#dddddd" lt 1 lw 1
set border lw 1.2

set key top right samplen 2 spacing 1.3 box lt -1 lc rgb "#555555" lw 1

set xrange [0:16]
set yrange [0:*]

# This is the key line to kill the white ring/halo
set pointintervalbox 0

plot \
    "fit.dat"   u 1:3:4  w filledcurves fs solid 1 lc rgb "light-blue" title "Uncertainty band", \
    "fit.dat"   u 1:2    w lines     lc rgb "#0066cc" lw 2.4 title "Best fit", \
    "data.dat"  u 1:2:3  w yerrorbars lc rgb "#c00000" pt 7 ps 0.5 lw 1.3 title "data"