set grid linestyle 1 lw 1,linestyle 3 lw 3
set border 9
set term png size 2000,1600 interlace enhanced font "Helvetica,40"
set output 'ans.png'
#set yrange [0:1]
#set xrange [0:1]
set key left bottom

set bars small
square(x)=x*x
plot 'fins.txt' w yerrorbars title 'data' pt 5 ps 1,-x/4+0.25 

