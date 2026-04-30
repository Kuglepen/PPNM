set terminal pdfcairo enhanced color font "Times,12" size 6in,4in
set output "erfplot.pdf"

set title "Error in erf(1) vs accuracy"
set xlabel "acc"
set ylabel "|error|"

set logscale x
set logscale y

set grid
set key top left

plot "erf_error.dat" using 1:2 with linespoints lw 2 title "error"