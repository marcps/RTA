set title "Evolució temporal TSTEP=0.05, T_0=0; T_F=500 wf=800 p2_f=800 NITER=4000"
set xlabel "tau*T"
set ylabel "tau*deri_tau{T}/(E+P_L)  -   1"
set grid
set terminal png size 1000,900 enhanced font "Helvetica,15"
set output 'graph2.png'

plot 'conserv.dat' u 1:2 w l title "EPS=0.2, m0=1, tau0=1"

