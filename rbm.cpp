#include "rbm.h"

RBM::RBM(int n_visible, int n_hidden, int mode){
    // 変数の用意
    this->n_visible = n_visible;
    this->n_hidden = n_hidden;
    this->visible_variable = new int[n_visible];
    this->hidden_variable = new int[n_hidden];
    this->W = new double*[n_visible];
    for(int i = 0; i < n_visible; i++){
        this->W[i] = new double[n_hidden];
    }
    this->b = new double[n_hidden];
    this->c = new double[n_visible];
    this->mode = mode;

    std::random_device rd;
    gen = std::mt19937(rd()); // 乱数生成器の初期化
    dis = std::uniform_real_distribution<double>(0.0, 1.0); // 0.0から1.0の範囲で乱数を生成

    // 変数の初期化
    for(int i = 0; i < n_visible; i++){
        for(int j = 0; j < n_hidden; j++){
            this->W[i][j] = 2*random_num() - 1;
        }
    }
    for(int i = 0; i < n_hidden; i++){
        this->b[i] = 2*random_num() - 1;
    }
    for(int i = 0; i < n_visible; i++){
        this->c[i] = 2*random_num() - 1;
    }
}

RBM::~RBM(){
    delete[] this->visible_variable;
    delete[] this->hidden_variable;
    for(int i = 0; i < n_visible; i++){
        delete[] this->W[i];
    }
    delete[] this->W;
    delete[] this->b;
    delete[] this->c;
}

double RBM::random_num(){
    return dis(gen);
}