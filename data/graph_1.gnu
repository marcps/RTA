set title "Evolució temporal NITER=1000, TNITER=10000, T_F=100"
set xlabel "tau*T"
set ylabel "T*tau^{1/3}"
set grid
set terminal png size 1000,900 enhanced font "Helvetica,20"
set output 'graph1.png'

plot 'temp.dat' u 1:2 w l title "EPS=0.2"

