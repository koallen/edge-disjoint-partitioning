set terminal postscript eps color blacktext "Helvetica" 30 linewidth 2 enhanced size 7in,5in
set output "test_plot.eps"

set xrange [0:1000]
set logscale y
unset mytics
set yrange [0:100000000]
set format y "%.0l*10^{%L}"

set key box
set key outside vert center right reverse
set key samplen 1
set key font ",28"

set xlabel "#Queries" offset 0,0.8
set ylabel "#Index entries" offset 1.0,0

set title "EDP Index Size" offset 0,-0.8

set lmargin 8
set tmargin 1.5

set border 7
set ytics nomirror
set xtics nomirror
set xtics 0,100,1000
set xtics rotate by -45
set xtics center offset 0,-0.5

#plot "output.txt" every 100 with linespoints ls 4 title "YouTube-2000", \
#     "output_500.txt" every 100 with linespoints ls 2 title "YouTube-500"
plot "output.txt" every 100::99 with linespoints ls 4 title "YouTube-500"
