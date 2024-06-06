# RBM
制限ボルツマンマシン(restricted Boltzmann machine, RBM)のリポジトリ

# ファイル構成
- rbm.h：RBMクラスのヘッダファイル
- rbm.cpp：RBMクラスのメンバ関数の実装が書いてあるファイル
- main.cpp：RBMのサンプリングを実行するプログラムが書いてあるファイル
- learn.cpp：RBMの学習を実行するプログラムが書いてあるファイル
- learn-sampling.cpp：RBMの学習をPCD法で行うプログラムが書いてあるファイル
- paramGen.cpp：パラメーター値をファイルに出力するプログラムが書いてあるファイル
- paramRead.cpp：パラメーター値をファイルから入力するプログラムが書いてあるファイル
- Makefile：makeコマンドを使えるようにするファイル
- plt：gnuplotのスクリプト用のディレクトリ
    - graph.plt：main.cpp用のgnuplotのスクリプト
    - learn.plt：learn.cpp用のgnuplotのスクリプト
    - learn-anime.plt：学習のアニメーションを行うgnuplotのスクリプト
    - learn-anime-sampling.plt：学習のアニメーションを行うgnuplotのスクリプト
    - paramGen.plt：paramGen.cpp用のgnuplotのスクリプト
    - paramRead.plt：paramRead.cpp用のgnuplotのスクリプト

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
