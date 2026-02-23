set terminal pdfcairo enhanced font "Arial,12"

# ERF PLOT
set output "erf_plot.pdf"

set title "Error function"
set xlabel "x"
set ylabel "erf(x)"
set key bottom right box

plot "erf_curve.dat" with lines lw 2 title "Approximation", \
     "erf_points.dat" with points pt 7 ps 0.8 title "Tabulated values"

# GAMMA PLOT
set output "gamma_plot.pdf"

set title "Gamma function"
set xlabel "x"
set ylabel "Gamma(x)"
set key bottom right box

# limit y-range to avoid huge spikes
set xrange [-4.5:4.5]
set yrange [-4.5:4.5]

plot "gamma_curve.dat" with lines lw 2 title "Gamma(x)", \
     "gamma_points.dat" with points pt 7 ps 0.8 title "Factorials"

# LOG-GAMMA PLOT
set output "lngamma_plot.pdf"

set title "Log Gamma function"
set xlabel "x"
set ylabel "ln(Gamma(x))"
set key bottom right box

unset yrange  # reset from previous plot
unset xrange

plot "lngamma_curve.dat" with lines lw 2 title "ln Gamma(x)", \
     "lngamma_points.dat" with points pt 6 ps 0.8 title "log tabulated"

# COMPLEX GAMMA (3D)
set output "gamma_complex.pdf"

set title "|Gamma(z)| in complex plane"
set xlabel "Re(z)"
set ylabel "Im(z)"
set zlabel "|Gamma(z)|"

set view 60, 315
set hidden3d
set pm3d at s

unset key
unset surface

set zrange [0:6]
set palette rgb 33,13,10
set xrange [-4:4]
set yrange [-4:4]

splot "gamma_complex.dat" using 1:2:3 with pm3d, \
      "" using 1:2:3 with lines lc "black" lw 0.5


# Finish output
set output