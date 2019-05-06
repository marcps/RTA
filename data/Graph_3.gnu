
set xlabel "tau*T"
set ylabel "(tau/T)*deltaT"

set grid
set terminal png size 1000,500 enhanced font "Helvetica,14"
set output 'graph3.png'

plot 'temp201.dat' u 1:2 w l title 'eps=0.1' ,'temp202.dat' u 1:2 w l title 'eps=0.2', 'temp203.dat' u 1:2 w l title 'eps=0.3','temp204.dat' u 1:2 w l title 'eps=0.4','temp208.dat' u 1:2 w l title 'eps=0.8'
