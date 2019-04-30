set title "Tempertatura en funció del temps propi amb E prop Tau^{-2}"
set xlabel "proper time"
set ylabel "T*tau^{1/3}"
set grid
set terminal png size 1000,800 enhanced font "Helvetica,25"
set output "graph.png"

plot "temp01.dat" using 1:2 with lines title "e=0.1","temp02.dat" using 1:2 with lines title "e=0.2","temp03.dat" using 1:2 with lines title "e=0.3","temp08.dat" using 1:2 with lines title "e=0.8","temp095.dat" using 1:2 with lines title "e=0.95"
