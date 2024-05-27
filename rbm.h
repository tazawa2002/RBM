// rbm.h 制限ボルツマンマシンのヘッダーファイル
#include <random>

#ifndef RBM_H
#define RBM_H

class RBM {
    public:
        RBM(int n_visible, int n_hidden, int mode);
        ~RBM();
    private:
        int* visible_variable;
        int* hidden_variable;
        int n_visible;
        int n_hidden;
        double** W;
        double* b;
        double* c;
        int mode;

        // 乱数生成器のメンバ変数
        std::mt19937 gen;
        std::uniform_real_distribution<double> dis;
        double random_num();
};

#endif

