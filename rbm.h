// rbm.h 制限ボルツマンマシンのヘッダーファイル
#include <random>

#ifndef RBM_H
#define RBM_H

class RBM {
    public:
        RBM(int v_num, int h_num);
        ~RBM();
        double energy_calc();
    private:
        int* v;
        int* h;
        int v_num;
        int h_num;
        double** W;
        double* b;
        double* c;

        // 乱数生成器のメンバ変数
        std::mt19937 gen;
        std::uniform_real_distribution<double> dis;
        double random_num();
};

#endif

