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

## コンパイル方法
以下のコマンドを実行すると実行ファイルが作成される
```shell
make
```

## サンプリングの実行
サンプリングの実行結果を表示する. `graph/graph.pdf`が生成される. 
```shell
./main
gnuplot ./plt/graph.plt
```

## 学習の実行
学習を実行する. `graph/learn.pdf`が生成される. 
```shell
./learn
gnuplot ./plt/learn.plt
```

## 学習のアニメーション
学習のアニメーションファイルを作成する. `graph/learn-anime.gif`が生成される. 
```shell
./learn
gnuplot ./plt/learn-anime.plt
```

## 学習の実行(PCD法で期待値計算)
学習を実行する. `graph/learn.pdf`が生成される. 
```shell
./learn
gnuplot ./plt/learn.plt
```

## 学習のアニメーション(PCD法で期待値計算)
学習のアニメーションファイルを作成する. `graph/learn-anime.gif`が生成される. 
```shell
./learn
gnuplot ./plt/learn-anime.plt
```


# 注意点
VL-PGothicというフォントがないとpdfの出力結果がおかしくなる
