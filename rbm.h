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
        int vStates;
        int hStates;
        int totalStates;
        double energy_calc();
        void p_distr_calc();
        void p_distr_v_calc();
        void update_v();
        void update_h();
        void sampling(int num);
        void dataGen(int num);
        void dataRead(int num);
        void train();
        vector<double> p_distr;
        vector<double> p_distr_v;
        vector<int> histgram;
        vector<int> histgram_v;
        int traindatanum;
        vector<vector<int> > traindata;
    private:
        vector<int> v;
        vector<int> h;
        vector< vector<double> > W;
        vector<double> b;
        vector<double> c;
        double sig(double x);

        void print();
        int state_num();
        int stateV();
        void setV(int num);

        // 乱数生成器のメンバ変数
        std::mt19937 gen;
        std::uniform_real_distribution<double> dis;
        double random_num();
};

#endif

