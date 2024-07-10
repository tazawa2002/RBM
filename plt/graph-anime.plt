set terminal gif animate delay 1 font "VL PGothic,10" size 720, 240
set output "./graph/graph-animate.gif"

# 縦軸の最大値を求める処理
stats './data/p_distr.dat' using 2
x = STATS_records
unset key
set xrange[-0.5:x-0.5]
set xlabel "状態"

# ファイル数を数える
file_count = system("ls ./data/sampling-*.dat | wc -l")
file_count = int(file_count)

do for [i=0:file_count-1]{
    set multiplot layout 1,2

    set ylabel "確率"
    set title "RBMの確率分布"
    plot "./data/p_distr.dat" smooth freq with boxes fill solid lc rgb "#006400"

    set ylabel "出現回数"
    set title "RBMのサンプリング結果"
    plot sprintf("./data/sampling-%03d.dat", i) smooth freq with boxes fill solid lc rgb "#006400"

    unset multiplot
}