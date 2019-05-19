set title "Evolució temporal T_0=1; T_F=20; TSTEP=0.05; NITER=1000; P2_0=0.0; P2_F=100; W0=0; WF=100; EPS=0.2;"
set xlabel "tau*T"
set ylabel "tau*deri_{tau}{T}/T"
set grid
set terminal png size 1000,900 enhanced font "Helvetica,10"
set output 'graph3.png'

plot 'tderie.dat' u 1:2 w l title "EPS=0.2, tau0=1",-0.3333333333333333333333 title "-1/3"

