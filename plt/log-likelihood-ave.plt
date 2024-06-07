set term pdfcairo size 6in, 4in font "VL PGothic,24"
set output "./graph/log-likelihood-ave.pdf"

set xlabel "学習回数"
set ylabel "対数尤度"

set key right bottom

set xrange [:1000]
set yrange [:-2]

plot "./data/log-likelihood-ave.dat" w l title "厳密計算", "./data/log-likelihood-ave-sampling.dat" w l title "サンプリング"

