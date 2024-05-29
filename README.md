# RBM
制限ボルツマンマシン(restricted Boltzmann machine, RBM)のリポジトリ

# ファイル構成
- rbm.h：RBMクラスのヘッダファイル
- rbm.cpp：RBMクラスのメンバ関数の実装が書いてあるファイル
- main.cpp：RBMのサンプリングを実行するプログラムが書いてあるファイル
- learn.cpp：RBMの学習を実行するプログラムが書いてあるファイル
- Makefile：makeコマンドを使えるようにするファイル
- graph.plt：サンプリング結果をグラフ化するgnuplotのスクリプト
- learn.plt：学習の結果をグラフ化するgnuplotのスクリプト

# 実行方法
## サンプリングの実行
```shell
make
./main
gnuplot graph.plt
```

## 学習の実行
```shell
make
./learn
gnuplot learn.plt
```

## 注意点
リポジトリにgraphとdataという名前のディレクトリを作成しないと実行したときエラーになる
VL-PGothicというフォントがないとpdfの出力結果がおかしくなる
