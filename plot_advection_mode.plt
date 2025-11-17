# Usage:    gnuplot -c plot_advection_mode.plt riemann_forward

mode = ARG1
print "Plotting mode =", mode

infile      = sprintf("result/advection_%s.dat", mode)
outfile     = sprintf("pic/advection_%s.png", mode)

set terminal pngcairo size 800,600
set output outfile

set title sprintf("Advection Result Final (%s)", mode)
set xlabel "x"
set ylabel "u(x)"

plot infile using 1:2 with linespoints lw 2 pt 7 title "Final"

unset output
