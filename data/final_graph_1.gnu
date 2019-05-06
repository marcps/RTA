set title 'CONSERVACIÓ DE LENERGIA'
set xlabel "tau*T"
set ylabel "abs(tau*deltaE/(E+P_L)) - 1"
set grid
set yrange [-2:2]
set terminal png size 1000,500 enhanced font "Helvetica,14"
set output 'graph2.png'

plot 'conserv01.dat' u 1:2 w l title 'eps=0.1','conserv02.dat' u 1:2 w l title 'eps=0.2', 'conserv08.dat' u 1:2 w l title "eps=0.8"
