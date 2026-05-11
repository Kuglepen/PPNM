set terminal pdfcairo enhanced color font "Times,18" size 14cm,9cm
set output "plot.pdf"

set title "Neural Network Approximation and Derivatives" font ",24"

set xlabel "x" font ",20"
set ylabel "Function / Antiderivative" font ",20"
set y2label "Derivatives" font ",20"

set xrange [-1:1]
set yrange [-1:1]
set y2range [-30:30]

set ytics nomirror
set y2tics

set border linewidth 1.5
set tics scale 0.75
set grid lw 1 dt 2

set key top right spacing 1.2 font ",16"

plot \
    "fit.txt" using 1:2 with lines lw 3 title "ANN fit", \
    "data.txt" using 1:2 with points pt 7 ps 1.2 title "Data", \
    "fit.txt" using 1:3 axes x1y2 with lines dt 2 lw 2 title "First derivative", \
    "fit.txt" using 1:4 axes x1y2 with lines dt 3 lw 2 title "Second derivative", \
    "fit.txt" using 1:5 with lines dt 4 lw 2 title "Antiderivative"