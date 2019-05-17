set title "Evolució temporal t_f=100;t_0=1; integration time step=0.5; m0=1.0; w_f=30.0; w_0=0.0; p2_f=300.0; p_0=0.0"
set xlabel "tau"
set ylabel "(E-E_eq)/E"
set yrange [-1:1]
set grid
set terminal png size 1000,900 enhanced font "Helvetica,10"
set output 'convergence2.png'

plot 'convergence2.dat' u 1:2 w l title "EPS=0.2"

