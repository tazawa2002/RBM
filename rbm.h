// rbm.h 制限ボルツマンマシンのヘッダーファイル
#include <iostream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

#ifndef RBM_H
#define RBM_H

class RBM {
    public:
        RBM(int v_num, int h_num);
        ~RBM();
        int totalStates;
        double energy_calc();
        void p_distr_calc();
        vector<double> p_distr;
    private:
        vector<int> v;
        vector<int> h;
        vector<vector<double>> W;
        vector<double> b;
        vector<double> c;

        // 乱数生成器のメンバ変数
        std::mt19937 gen;
        std::uniform_real_distribution<double> dis;
        double random_num();
};

#endif

