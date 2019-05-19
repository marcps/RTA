set title "Evolució temporal NITER=2000, TSTEP=0.25, T_0=0; T_F=500"
set xlabel "tau*T"
set ylabel "deri_{tau}{E}/E"
set grid
set terminal png size 1000,900 enhanced font "Helvetica,20"
set output 'graph4.png'

plot 'ederie.dat' u 2:1 w l title "EPS=0.2, tau0=1"

