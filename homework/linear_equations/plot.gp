set terminal pdfcairo enhanced color font "Times-New-Roman,12" size 6in,4in
set output "qr_timing.pdf"

set title "QR Decomposition Complexity"
set xlabel "Matrix size N"
set ylabel "Time (s)"

set grid back lc rgb "#dddddd" lt 1 lw 1
set border lw 1.2

set key top left samplen 2 spacing 1.3 box lt -1 lc rgb "#555555" lw 1

set xrange [0:*]
set yrange [0:*]

# Fit function
f(x) = a*x**3

fit f(x) "data.dat" via a

plot \
    "data.dat" using 1:2 with points pt 7 ps 0.8 lc rgb "#c00000" title "Measured data", \
    f(x) with lines lc rgb "#0066cc" lw 2.4 title sprintf("Fit: a*x^3 (a=%.2e)", a)