set term pdfcairo size 12in, 4in font "VL-PGothic-Regular.ttf,24"
set output "./graph/graph.pdf"

# 縦軸の最大値を求める処理
stats './data/p_distr.dat' using 2
ymax1 = STATS_max
x = STATS_records

stats './data/histgram.dat' using 2
ymax2 = STATS_max

ymax = ymax1 > ymax2 ? ymax1 : ymax2

unset key
set multiplot layout 1,2
set yrange[0:ymax*1.1]
set xlabel "状態"
set ylabel "確率"

set title "RBMの確率分布"
plot "./data/p_distr.dat" smooth freq with boxes fill solid

set title "RBMのサンプリング結果"
plot "./data/histgram.dat" smooth freq with boxes fill solid

unset multiplot