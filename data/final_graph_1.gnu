set xlabel "tau*T"
set ylabel "tau*deltaE+E+P_L"
set grid
set terminal png size 1000,500 enhanced font "Helvetica,14"
set output 'graph2.png'

plot 'conserv.dat' u 1:2 w l 
