set terminal pdfcairo enhanced font "Times,12" size 10cm,7cm
set output 'fig_waves.pdf'

set xlabel "r (Bohr radii)"
set ylabel "f(r)"
set grid lw 1 dt 2
set key box

set samples 500   # smoother analytic curve

plot "waves.dat" using 1:2 with lines lw 3 title "Ground state", \
     "waves.dat" using 1:3 with lines lw 2 dt 2 title "1st excited", \
     "waves.dat" using 1:4 with lines lw 2 dt 3 title "2nd excited", \
     2*x*exp(-x) with lines lw 2 dt 4 title "Exact ground state"