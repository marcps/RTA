set title "Evolució temporal NITER=1000, TNITER=10000, T_F=100"
set xlabel "tau*T"
set ylabel "tau*deri_{tau}{T}/T"
set grid
set terminal png size 1000,900 enhanced font "Helvetica,20"
set output 'graph3.png'

plot 'temp1.dat' u 1:2 w l title "EPS=0.2, tau0=1",-0.3333333333333333333333 title "-1/3"

