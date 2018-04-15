gnuplot plot_100.gnu
gnuplot plot_1000.gnu
convert -flatten -density 300 -size 1400x1000 plot_100.eps plot_100.png
convert -flatten -density 300 -size 1400x1000 plot_1000.eps plot_1000.png
