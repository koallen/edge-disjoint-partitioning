set terminal postscript eps color blacktext "Helvetica" 30 linewidth 4 enhanced size 7in,5in
set output "plot_1000.eps"

#set logscale y
#set format y "%.0l*10^{%L}"
set yrange [8000000:15000000]
#unset mytics

set key box
set key outside vert center right reverse
set key samplen 1
set key font ",28"

set xlabel "#Queries" offset 0,0.8
set ylabel "#Index entries" offset 1.8,0

set title "EDP Index Size" offset 0,-0.8

set lmargin 8.8
set tmargin 1.5

set border 7
set ytics nomirror
set xtics nomirror
set xtics rotate by -45
set xtics center offset 0,-0.5

set xrange [0:1000]
set xtics 0,100,1000
plot "youtube.txt" every 100::99 with linespoints ls 4 title "YouTube-2000", \
     "biogrid.txt" every 100::99 with linespoints ls 2 title "BioGrid-10000"
