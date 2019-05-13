set title "Evolució temporal"
set xlabel "tau*T"
set ylabel "T*tau^{1/3}"
set grid
set terminal png size 1700,2000 enhanced font "Helvetica,20"
set output 'graph1.png'

plot 'temp.dat' u 1:2 w l title "EPS=0.2, m0=1, tau0=1"

