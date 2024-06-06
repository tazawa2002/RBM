set terminal gif animate delay 1 font "VL PGothic,10" size 720, 480
set output "./graph/learn-animate.gif"

# 縦軸の最大値を求める処理
stats './data/rbm1_p.dat' using 2
ymax1 = STATS_max
x = STATS_records

stats './data/rbm1_q.dat' using 2
ymax2 = STATS_max

stats './data/rbm2_p.dat' using 2
ymax3 = STATS_max

stats './data/rbm2_q.dat' using 2
ymax4 = STATS_max

ymax_p = ymax1 > ymax3 ? ymax1 : ymax3
ymax_q = ymax2 > ymax4 ? ymax2 : ymax4

unset key

# ファイル数を数える
file_count = system("ls ./data/learn-v-*.txt | wc -l")
file_count = int(file_count)

do for [i=0:file_count-1]{
    set multiplot layout 2,2
    set xlabel "状態"
    set ylabel "確率"
    set xrange [-0.5:x-0.5]
    set yrange[0:ymax_p*1.1]

    set title "生成モデルの確率分布"
    plot "./data/rbm1_p.dat" with boxes fill solid lc rgb "#006400"

    set title "学習モデルの確率分布"
    plot sprintf("./data/learn-v-%03d.txt", i) with boxes fill solid lc rgb "#006400"

    set ylabel "出現回数"
    set title "生成モデルのサンプリング結果"
    set yrange[0:ymax_q*1.1]
    plot "./data/rbm1_q.dat" with boxes fill solid lc rgb "#006400"
    # plot "./data/data.dat" smooth freq with boxes fill solid

    set title "学習モデルのサンプリング結果"
    plot "./data/rbm2_q.dat" with boxes fill solid lc rgb "#006400"

    unset multiplot
}