set key right vertical outside center box
set title 'Threshold'
set xlabel 'Selection'
set term postscript enhanced eps "Times-Roman" 12
set yrange [*:*]
set output 'thresh.eps'
plot 'thresh.txt' using 1:2 with linespoints t '0.0', 'thresh.txt' using 1:3 with linespoints t '0.1', 'thresh.txt' using 1:4 with linespoints t '0.2', 'thresh.txt' using 1:5 with linespoints t '0.3', 'thresh.txt' using 1:6 with linespoints t '0.4', 'thresh.txt' using 1:7 with linespoints t '0.5', 'thresh.txt' using 1:8 with linespoints t '0.6'
set term x11
