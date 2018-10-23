set key right vertical outside center box
set title 'Av.Quality'
set xlabel 'Selection'
plot 'AvQuality.tex' using 1:6 with linespoints t '0.5', 'AvQuality.tex' using 1:7 with linespoints t '0.6', 'AvQuality.tex' using 1:8 with linespoints t '0.7'
