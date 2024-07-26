set term pdfcairo size 6in, 4in font "VL PGothic,24"
set output "./graph/log-likelihood-ave-exact.pdf"

set xlabel "学習回数"
set ylabel "対数尤度"

set key right bottom

set xrange [:100]
set yrange [:]

plot "./data/log-likelihood-ave-nomal-exact.dat" w l linewidth 3 title "普通の勾配法", \
     "./data/log-likelihood-ave-momentum-exact.dat" w l linewidth 3 title "モーメンタム法", \
     "./data/log-likelihood-ave-adagrad-exact.dat" w l linewidth 3 title "AdaGrad", \
     "./data/log-likelihood-ave-rmsprop-exact.dat" w l linewidth 3 title "RMSprop", \
     "./data/log-likelihood-ave-adadelta-exact.dat" w l linewidth 3 title "AdaDelta", \
     "./data/log-likelihood-ave-adam-exact.dat" w l linewidth 3 title "Adam"

set output "./graph/log-likelihood-ave-sampling.pdf"

set xlabel "学習回数"
set ylabel "対数尤度"

set key right bottom

set xrange [:100]
set yrange [:]

plot "./data/log-likelihood-ave-nomal-sampling.dat" w l linewidth 3 title "普通の勾配法", \
     "./data/log-likelihood-ave-momentum-sampling.dat" w l linewidth 3 title "モーメンタム法", \
     "./data/log-likelihood-ave-adagrad-sampling.dat" w l linewidth 3 title "AdaGrad", \
     "./data/log-likelihood-ave-rmsprop-sampling.dat" w l linewidth 3 title "RMSprop", \
     "./data/log-likelihood-ave-adadelta-sampling.dat" w l linewidth 3 title "AdaDelta", \
     "./data/log-likelihood-ave-adam-sampling.dat" w l linewidth 3 title "Adam"


set term pngcairo size 900, 600 font "VL PGothic,24"
set output "./graph/log-likelihood-ave-exact.png"

set xlabel "学習回数"
set ylabel "対数尤度"

set key right bottom

set xrange [:100]
set yrange [:]

plot "./data/log-likelihood-ave-nomal-exact.dat" w l linewidth 3 title "普通の勾配法", \
     "./data/log-likelihood-ave-momentum-exact.dat" w l linewidth 3 title "モーメンタム法", \
     "./data/log-likelihood-ave-adagrad-exact.dat" w l linewidth 3 title "AdaGrad", \
     "./data/log-likelihood-ave-rmsprop-exact.dat" w l linewidth 3 title "RMSprop", \
     "./data/log-likelihood-ave-adadelta-exact.dat" w l linewidth 3 title "AdaDelta", \
     "./data/log-likelihood-ave-adam-exact.dat" w l linewidth 3 title "Adam"

set output "./graph/log-likelihood-ave-sampling.png"

set xlabel "学習回数"
set ylabel "対数尤度"

set key right bottom

set xrange [:100]
set yrange [:]

plot "./data/log-likelihood-ave-nomal-sampling.dat" w l linewidth 3 title "普通の勾配法", \
     "./data/log-likelihood-ave-momentum-sampling.dat" w l linewidth 3 title "モーメンタム法", \
     "./data/log-likelihood-ave-adagrad-sampling.dat" w l linewidth 3 title "AdaGrad", \
     "./data/log-likelihood-ave-rmsprop-sampling.dat" w l linewidth 3 title "RMSprop", \
     "./data/log-likelihood-ave-adadelta-sampling.dat" w l linewidth 3 title "AdaDelta", \
     "./data/log-likelihood-ave-adam-sampling.dat" w l linewidth 3 title "Adam"
