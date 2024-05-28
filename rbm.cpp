#include "rbm.h"

// コンストラクタ
RBM::RBM(int v_num, int h_num){
    // 変数の用意
    this->totalStates = pow(2,(v_num + h_num));
    this->v.resize(v_num);
    this->h.resize(h_num);
    this->W.resize(v_num);
    for(int i=0;i<v_num;i++){
        this->W[i].resize(h_num);
    }
    this->b.resize(v_num);
    this->c.resize(h_num);
    this->p_distr.resize(this->totalStates);
    this->histgram.resize(this->totalStates);

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
    int i,j,k;
    double Z = 0;

    // すべての状態の確率を求める
    for(i=0;i<totalStates;i++){
        // 状態を設定
        for(k=0;k<v.size();k++){
            v[k] = (i >> k)&1;
        }
        for(k=0;k<h.size();k++){
            h[k] = (i >> (k+v.size()))&1;
        }
        p_distr[i] = exp(-energy_calc());
    }
    for(i=0;i<this->totalStates;i++){
        Z += p_distr[i];
    }
    for(i=0;i<totalStates;i++){
        p_distr[i] = p_distr[i] / Z;
    }
}

// 可視層の状態を更新
void RBM::update_v(){
    int i, j;
    double lambda;
    double p, u;
    for(i=0;i<v.size();i++){
        lambda = b[i];
        for(j=0;j<h.size();j++){
            lambda += W[i][j]*h[j];
        }
        p = sig(lambda);
        u = random_num();
        if(p >= u){
            v[i] = 1;
        }else{
            v[i] = 0;
        }
    }
}

// 隠れ層の状態を更新
void RBM::update_h(){
    int i, j;
    double lambda;
    double p, u;
    for(j=0;j<h.size();j++){
        lambda = c[i];
        for(i=0;i<v.size();i++){
            lambda += W[i][j]*v[j];
        }
        p = sig(lambda);
        u = random_num();
        if(p >= u){
            h[j] = 1;
        }else{
            h[j] = 0;
        }
    }
}

// サンプリング
void RBM::sampling(int num){
    int i, j;
    for(i=0;i<totalStates;i++){
        histgram[i] = 0;
    }

    for(i=0;i<1000;i++){
        update_v();
        update_h();
    }

    for(i=0;i<num;i++){
        for(j=0;j<10;j++){
            update_v();
            update_h();
        }
        // print();
        histgram[state_num()] += 1;
    }
}

// シグモイド関数
double RBM::sig(double x){
    double exp_val;
    if(x>0){
        return 1 / ( 1 + exp(-x) );
    }else{
        exp_val = exp(x);
        return exp_val / ( 1 + exp_val);
    }
}

void RBM::print(){
    int i;
    printf("data:");
    for(i=0;i<v.size();i++){
        printf("%d ", v[i]);
    }
    for(i=0;i<h.size();i++){
        printf("%d ", h[i]);
    }
    printf("\n");
}

int RBM::state_num(){
    int i;
    int state = 0;
    for(i=0;i<v.size();i++){
        state += v[i] << i;
    }
    for(i=0;i<h.size();i++){
        state += h[i] << (i+v.size());
    }
    return state;
}