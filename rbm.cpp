#include "rbm.h"

// コンストラクタ
RBM::RBM(int v_num, int h_num){
    // 変数の用意
    this->totalStates = 1 << (v_num + h_num);
    this->v.resize(v_num);
    this->h.resize(h_num);
    this->W.resize(v_num);
    for(int i=0;i<v_num;i++){
        this->W[i].resize(h_num);
    }
    this->b.resize(v_num);
    this->c.resize(h_num);
    this->p_distr.resize(this->totalStates);

    std::random_device rd;
    gen = std::mt19937(rd()); // 乱数生成器の初期化
    dis = std::uniform_real_distribution<double>(0.0, 1.0); // 0.0から1.0の範囲で乱数を生成

    // 変数の初期化
    for(int i = 0; i < this->v.size(); i++){
        for(int j = 0; j < this->h.size(); j++){
            this->W[i][j] = 2*random_num() - 1;
        }
    }
    for(int i = 0; i < this->v.size(); i++){
        this->b[i] = 2*random_num() - 1;
    }
    for(int i = 0; i < this->h.size(); i++){
        this->c[i] = 2*random_num() - 1;
    }
}

// デストラクタ
RBM::~RBM(){
    int i;
    i = 0;
}

// 0.0から1.0の範囲で乱数を生成
double RBM::random_num(){
    return dis(gen);
}

// エネルギーを計算する関数
double RBM::energy_calc(){
    int i,j;
    double energy = 0;
    for(i=0;i<this->v.size();i++){
        for(j=0;j<this->h.size();j++){
            energy -= W[i][j]*v[i]*h[j];
        }
        energy -= b[i]*v[i] + c[i]*h[i];
    }
    return energy;
}

// 確率を計算
void RBM::p_distr_calc(){
    int i,j;
    double Z = 0;

    for(i=0;i<totalStates;i++){
        // setX(i); 状態を設定
        p_distr[i] = exp(-energy_calc());
    }
    for(i=0;i<this->totalStates;i++){
        Z += p_distr[i];
    }
    for(i=0;i<totalStates;i++){
        p_distr[i] = p_distr[i] / Z;
    }   
}