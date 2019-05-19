set title "Evolució temporal T_0=1; T_F=20; TSTEP=0.05; NITER=1000; P2_0=0.0; P2_F=100; W0=0; WF=100; EPS=0.2;"
set xlabel "tau*T"
set ylabel "deri_{tau}{E}/E"
set grid
set terminal png size 1000,900 enhanced font "Hack,15"
set output 'graph4.png'

plot 'ederie.dat' u 2:1 w l title "EPS=0.2, tau0=1"

