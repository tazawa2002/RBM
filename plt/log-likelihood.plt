set term pdfcairo size 6in, 4in font "VL PGothic,24"
set output "./graph/log-likelihood.pdf"

set xlabel "学習回数"
set ylabel "対数尤度"

set key right bottom
set xrange [0:200]
set yrange [:]

plot "./data/log_likelihood.dat" w l title "対数尤度"

