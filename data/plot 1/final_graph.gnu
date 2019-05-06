set xlabel "tau"
set ylabel "T*tau^{1/3}"
set grid
set terminal png size 1000,500 enhanced font "Helvetica,14"
set output 'graph1.png'

plot 'temp.dat' u 1:2 w l,'temp02.dat' u 1:2 w l, 'temp03.dat' u 1:2 w l, 'temp08.dat' u 1:2 w l,'temp01.dat' u 1:2 w l
