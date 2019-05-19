set title "Evolució temporal T_0=1; T_F=200; TSTEP=0.25; NITER=4000; P2_0=0.0; P2_F=600; W0=0; WF=600; EPS=0.2;"
set xlabel "tau*T"
set ylabel "T*tau^{1/3}"
set grid
set terminal png size 1000,900 enhanced font "Hack,10"
set output 'graph1.png'

plot 'temp.dat' u 1:2 w l title "EPS=0.2"

