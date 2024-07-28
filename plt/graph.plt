set term pdfcairo size 18in, 4in font "VL PGothic,24"
set output "./graph/graph.pdf"

# 縦軸の最大値を求める処理
stats './data/p_distr.dat' using 2
ymax1 = STATS_max
x = STATS_records

stats './data/histgram.dat' using 2
ymax2 = STATS_max

unset key
set multiplot layout 1,3
set xrange[-0.5:x-0.5]
set xlabel "状態"
set ylabel "確率"

set yrange[0:ymax1*1.1]
set title "RBMの確率分布"
plot "./data/p_distr.dat" smooth freq with boxes fill solid lc rgb "#006400"

set yrange[0:ymax2*1.1]
set title "RBMのサンプリング結果"
set ylabel "出現回数"
plot "./data/histgram.dat" smooth freq with boxes fill solid lc rgb "#006400"

set xrange[0:10000]
unset yrange
set title "KLダイバージェンス"
set xlabel "サンプリング回数"
set ylabel "KLダイバージェンス"
plot "./data/KL.dat" w l lc rgb "#006400"

unset multiplot

set term pngcairo size 18in, 4in font "VL PGothic,10"
set output "./graph/graph.png"

# 縦軸の最大値を求める処理
stats './data/p_distr.dat' using 2
ymax1 = STATS_max
x = STATS_records

stats './data/histgram.dat' using 2
ymax2 = STATS_max

unset key
set multiplot layout 1,3
set xrange[-0.5:x-0.5]
set xlabel "状態"
set ylabel "確率"

set yrange[0:ymax1*1.1]
set title "RBMの確率分布"
plot "./data/p_distr.dat" smooth freq with boxes fill solid lc rgb "#006400"

set yrange[0:ymax2*1.1]
set title "RBMのサンプリング結果"
set ylabel "出現回数"
plot "./data/histgram.dat" smooth freq with boxes fill solid lc rgb "#006400"

set xrange[0:10000]
unset yrange
set title "KLダイバージェンス"
set xlabel "サンプリング回数"
set ylabel "KLダイバージェンス"
plot "./data/KL.dat" w l lc rgb "#006400"

unset multiplot