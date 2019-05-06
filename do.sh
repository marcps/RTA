#!/bin/bash
./MAKE
bin/EXEC temp01.dat conserv01.dat temp201.dat
read  -n 1 -p "Change to 02" noimporta
./MAKE
bin/EXEC temp02.dat conserv02.dat temp202.dat
read  -n 1 -p "Change to 03" noimporta
./MAKE
bin/EXEC temp03.dat conserv03.dat temp203.dat
read  -n 1 -p "Change to 04" noimporta
./MAKE
bin/EXEC temp04.dat conserv04.dat temp204.dat
read  -n 1 -p "Change to 08" noimporta
./MAKE
bin/EXEC temp08.dat conserv08.dat temp208.dat

