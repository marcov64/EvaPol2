set key bottom horizontal bmargin outside center nobox
set title 'Quality-Indicator Correlation'
set xlabel 'Orientation'
set yrange [0:0.8]
set term postscript enhanced eps "Times-Roman" 12
set output 'corrqx.eps'
plot 'corrqx.txt' using 1:3 with linespoints t 'Before orientation', 'corrqx.txt' using 1:2 with linespoints t 'After orientation'
set term x11
