set xlabel "tau"
set ylabel "T*tau^{1/3}"
set grid
set terminal png size 1000,500 enhanced font "Helvetica,14"
set output 'graph1.png'

plot 'temp01.dat' u 1:2 w l title 'eps=0.1' ,'temp02.dat' u 1:2 w l title 'eps=0.2', 'temp03.dat' u 1:2 w l title 'eps=0.3','temp04.dat' u 1:2 w l title 'eps=0.4','temp08.dat' u 1:2 w l title 'eps=0.8'
