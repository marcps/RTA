set title "Evolució temporal NITER=2000, TSTEP=0.25, T_0=0; T_F=500"
set xlabel "tau*T"
set ylabel "T*tau^{1/3}"
set grid
set terminal png size 1000,900 enhanced font "Helvetica,20"
set output 'graph1.png'

plot 'temp.dat' u 1:2 w l title "EPS=0.2"

