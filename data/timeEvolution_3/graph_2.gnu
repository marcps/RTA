set title "Evolució temporal NITER=2000, TSTEP=0.25, T_0=0; T_F=500"
set xlabel "tau*T"
set ylabel "tau*deri_tau{T}/(E+P_L)  -   1"
set grid
set terminal png size 1000,900 enhanced font "Helvetica,20"
set output 'graph2.png'

plot 'conserv.dat' u 1:2 w l title "EPS=0.2, m0=1, tau0=1"

