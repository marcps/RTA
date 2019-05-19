set title "EEvolució temporal T_0=1; T_F=20; TSTEP=0.05; NITER=1000; P2_0=0.0; P2_F=100; W0=0; WF=100; EPS=0.2;"
set xlabel "tau*T"
set ylabel "tau*deri_tau{T}/(E+P_L)  -   1"
set grid
set terminal png size 1000,900 enhanced font "Helvetica,10"
set output 'graph2.png'

plot 'conserv.dat' u 1:2 w l title "EPS=0.2, m0=1, tau0=1"

