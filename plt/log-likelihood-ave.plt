set term pdfcairo size 6in, 4in font "VL PGothic,24"
set output "./graph/log-likelihood-ave.pdf"

set xlabel "学習回数"
set ylabel "対数尤度"

set key right bottom

set xrange [:100]
set yrange [:]

plot "./data/log-likelihood-ave-nomal.dat" w l linewidth 3 title "普通の勾配法", \
     "./data/log-likelihood-ave-momentum.dat" w l linewidth 3 title "モーメンタム法", \
     "./data/log-likelihood-ave-adagrad.dat" w l linewidth 3 title "AdaGrad", \
     "./data/log-likelihood-ave-rmsprop.dat" w l linewidth 3 title "RMSProp"

