set term pdfcairo size 12in, 8in font "VL PGothic,24"
set output "./graph/learn_v.pdf"
set grid

# 縦軸の最大値を求める処理
stats './data/rbm1_p.dat' using 2
ymax1 = STATS_max
x = STATS_records

stats './data/rbm2_p.dat' using 2
ymax2 = STATS_max

stats './data/rbm1_q.dat' using 2
ymax3 = STATS_max

stats './data/rbm2_q.dat' using 2
ymax4 = STATS_max

ymax = ymax1 > ymax2 ? ymax1 : ymax2
# ymax = ymax > ymax3 ? ymax : ymax3
# ymax = ymax > ymax4 ? ymax : ymax4

unset key
set multiplot layout 2,2 spacing 0.5,0.5
set yrange [0:ymax*1.1]
set xrange [-0.5:x-0.5]
set xlabel "状態"
set ylabel "確率"

set title "生成モデルの確率分布"
plot "./data/rbm1_p.dat" with boxes fill solid lc rgb "#006400"

set title "学習モデルの確率分布"
plot "./data/rbm2_p.dat" with boxes fill solid lc rgb "#006400"

unset yrange
set ylabel "出現回数"
set title "生成モデルのサンプリング結果"
plot "./data/rbm1_q.dat" with boxes fill solid lc rgb "#006400"
# plot "./data/data.dat" smooth freq with boxes fill solid

set title "学習モデルのサンプリング結果"
plot "./data/rbm2_q.dat" with boxes fill solid lc rgb "#006400"

unset multiplot