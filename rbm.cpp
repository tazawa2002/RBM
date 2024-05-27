#include "rbm.h"

RBM::RBM(int v_num, int h_num){
    // 変数の用意
    this->v_num = v_num;
    this->h_num = h_num;
    this->v = new int[v_num];
    this->h = new int[h_num];
    this->W = new double*[v_num];
    for(int i = 0; i < v_num; i++){
        this->W[i] = new double[h_num];
    }
    this->b = new double[h_num];
    this->c = new double[v_num];

    std::random_device rd;
    gen = std::mt19937(rd()); // 乱数生成器の初期化
    dis = std::uniform_real_distribution<double>(0.0, 1.0); // 0.0から1.0の範囲で乱数を生成

    // 変数の初期化
    for(int i = 0; i < v_num; i++){
        for(int j = 0; j < h_num; j++){
            this->W[i][j] = 2*random_num() - 1;
        }
    }
    for(int i = 0; i < h_num; i++){
        this->b[i] = 2*random_num() - 1;
    }
    for(int i = 0; i < v_num; i++){
        this->c[i] = 2*random_num() - 1;
    }
}

RBM::~RBM(){
    delete[] this->v;
    delete[] this->h;
    for(int i = 0; i < v_num; i++){
        delete[] this->W[i];
    }
    delete[] this->W;
    delete[] this->b;
    delete[] this->c;
}

double RBM::random_num(){
    return dis(gen);
}

double RBM::energy_calc(){
    int i,j;
    double energy = 0;
    for(i=0;i<v_num;i++){
        for(j=0;j<h_num;j++){
            energy -= W[i][j]*v[i]*h[j];
        }
        energy -= b[i]*v[i] + c[i]*h[i];
    }
    return energy;
}