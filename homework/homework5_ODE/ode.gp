set terminal pdfcairo enhanced color font "Times,12" size 6in,4in
set output "ode.pdf"

set title "Damped Oscillator"
set xlabel "x"
set ylabel "State variables"

set grid
set key top right

plot "ode.dat" using 1:2 with lines lw 2 title "theta(x)", \
     "ode.dat" using 1:3 with lines lw 2 title "omega(x)"