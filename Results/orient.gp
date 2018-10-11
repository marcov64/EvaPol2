set key right vertical outside center box
set title 'Av.Orientation'
set xlabel 'Selection'
set term postscript enhanced eps "Times-Roman" 12
set output 'orient.eps'
plot 'Orient.txt' using 1:2 with linespoints t '0.0', 'Orient.txt' using 1:3 with linespoints t '0.1', 'Orient.txt' using 1:4 with linespoints t '0.2', 'Orient.txt' using 1:5 with linespoints t '0.3', 'Orient.txt' using 1:6 with linespoints t '0.4', 'Orient.txt' using 1:7 with linespoints t '0.5', 'Orient.txt' using 1:8 with linespoints t '0.6', 'Orient.txt' using 1:9 with linespoints t '0.7'
set term x11
