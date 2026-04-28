set terminal pdfcairo enhanced color font "Times,12" size 6in,6in
set output "orbit.pdf"

set title "Relativistic Orbit (different ε)"
set xlabel "x"
set ylabel "y"

set size ratio -1
set grid
set key top right

plot "orbit.dat" index 0 using (cos($1)/$2):(sin($1)/$2) w l lw 2 title "circular", \
     "orbit.dat" index 1 using (cos($1)/$2):(sin($1)/$2) w l lw 2 title "ellipse", \
     "orbit.dat" index 2 using (cos($1)/$2):(sin($1)/$2) w l lw 2 title "relativistic", \
     '-' using 1:2 with points pt 3 ps 2 lc rgb "orange" title "star"
0 0
e