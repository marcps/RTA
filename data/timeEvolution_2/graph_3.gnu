set title "Evolució temporal NITER=2000, TSTEP=0.25, T_0=0; T_F=500"
set xlabel "tau*T"
set ylabel "tau*deri_{tau}{T}/T"
set grid
set terminal png size 1000,900 enhanced font "Helvetica,20"
set output 'graph3.png'

plot 'tderie.dat' u 1:2 w l title "EPS=0.2, tau0=1",-0.3333333333333333333333 title "-1/3"

