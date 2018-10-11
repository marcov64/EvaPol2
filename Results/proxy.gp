set key right vertical outside center box
set title 'Av.Indicator'
set xlabel 'Selection'
set term postscript enhanced eps "Times-Roman" 12
set output 'proxy.eps'
plot 'AvProxy.txt' using 1:2 with linespoints t '0.1', 'AvProxy.txt' using 1:3 with linespoints t '0.2','AvProxy.txt' using 1:4 with linespoints t '0.3', 'AvProxy.txt' using 1:5 with linespoints t '0.4', 'AvProxy.txt' using 1:6 with linespoints t '0.5', 'AvProxy.txt' using 1:7 with linespoints t '0.6', 'AvProxy.txt' using 1:8 with linespoints t '0.7'
set term x11
