set terminal postscript eps color blacktext "Helvetica" 30 linewidth 4 enhanced size 7in,5in
set output "plot_100.eps"

unset mytics

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
set xtics rotate by -45
set xtics center offset 0,-0.5

set yrange [0:]
set xrange [0:100]
set xtics 0,10,100
plot "youtube.txt" every 10::::100 with lines lw 2 title "YouTube-2000", \
     "biogrid.txt" every 10::::100 with lines lw 2 title "BioGrid-10000"
