set key bottom horizontal outside center box
set title 'Quality-Indicator Correlation'
set xlabel 'Orientation'
set term postscript enhanced eps "Times-Roman" 12
set output 'corrqx.eps'
plot 'corrqx.txt' using 1:3 with linespoints t 'Before orientation', 'corrqx.txt' using 1:2 with linespoints t 'After orientation'
set term x11
