set xlabel "tau*T"
set ylabel "(tau/T)*deltaT"
set grid
set terminal png size 1000,500 enhanced font "Helvetica,14"
set output 'graph3.png'

plot 'temp2.dat' u 1:2 w l ,-0.33333333333333333333 title "1/3"
