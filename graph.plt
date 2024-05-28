set term pdfcairo size 12in, 4in font "VL-PGothic-Regular.ttf,24"
set output "./graph.pdf"



set multiplot layout 1,2

plot "./data/p_distr.dat" smooth freq with boxes fill solid
plot "./data/histgram.dat" smooth freq with boxes fill solid

unset multiplot