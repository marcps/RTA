set title "step=0.25 Evolució temporal t_f=100; t_0=1; integration time step=0.5; m0=1.0; w_f=200; w_0=0; p2_f=200; p_0=0"
set xlabel "tau"
set ylabel "(E-E_eq)/E"
set yrange [-1:1]
set grid
set terminal png size 1000,900 enhanced font "Helvetica,10"
set output 'convergence6.png'

plot 'convergence6.dat' u 1:2 w l title "EPS=0.2"

