set terminal gif animate delay 1 font "VL PGothic,10"
set size 720, 480
set output "./graph/learn-animate-vh.gif"

# 縦軸の最大値を求める処理
stats './data/p_distr1.dat' using 2
ymax1 = STATS_max
x = STATS_records

stats './data/histgram1.dat' using 2
ymax2 = STATS_max

stats './data/p_distr2.dat' using 2
ymax3 = STATS_max

stats './data/histgram2.dat' using 2
ymax4 = STATS_max

ymax = ymax1 > ymax2 ? ymax1 : ymax2
ymax = ymax > ymax3 ? ymax : ymax3
ymax = ymax > ymax4 ? ymax : ymax4

unset key
set xrange [-0.5:x-0.5]
set yrange[0:ymax*1.1]
set xlabel "状態"
set ylabel "確率"

# ファイル数を数える
file_count = system("ls ./data/learn-vh-*.txt | wc -l")
file_count = int(file_count)

do for [i=0:file_count-1]{
    set multiplot layout 2,2

    set title "生成モデルの確率分布"
    plot "./data/p_distr1.dat" smooth freq with boxes fill solid lc rgb "#006400"

    set title "学習モデルの確率分布"
    filename = sprintf("./data/learn-vh-%03d.txt", i)
    plot filename smooth freq with boxes fill solid lc rgb "#006400"

    set title "生成モデルのサンプリング結果"
    plot "./data/histgram1.dat" smooth freq with boxes fill solid lc rgb "#006400"

    set title "学習モデルのサンプリング結果"
    plot "./data/histgram2.dat" smooth freq with boxes fill solid lc rgb "#006400"

    unset multiplot
}