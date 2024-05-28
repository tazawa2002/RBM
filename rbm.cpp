#include "rbm.h"

// コンストラクタ
RBM::RBM(int v_num, int h_num){
    // 変数の用意
    this->vStates = pow(2,v_num);
    this->hStates = pow(2,h_num);
    this->totalStates = this->vStates*this->hStates;
    this->v.resize(v_num);
    this->h.resize(h_num);
    this->W.resize(v_num);
    for(int i=0;i<v_num;i++){
        this->W[i].resize(h_num);
    }
    this->b.resize(v_num);
    this->c.resize(h_num);
    this->p_distr.resize(this->totalStates);
    this->p_distr_v.resize(this->vStates);
    this->histgram.resize(this->totalStates);
    this->histgram_v.resize(this->vStates);

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
    }
    for(i=0;i<this->v.size();i++){
        energy -= b[i]*v[i];
    }
    for(j=0;j<this->h.size();j++){
        energy -= c[j]*h[j];
    }
    return energy;
}

// 確率を計算
void RBM::p_distr_calc(){
    int i,j,k;
    double Z = 0;

    // すべての状態の確率を求める
    for(k=0;k<totalStates;k++){
        // 状態を設定
        for(i=0;i<v.size();i++){
            v[i] = (k >> i)&1;
        }
        for(j=0;j<h.size();j++){
            h[j] = (k >> (j+v.size()))&1;
        }
        p_distr[k] = exp(-energy_calc());
    }
    for(i=0;i<this->totalStates;i++){
        Z += p_distr[i];
    }
    for(i=0;i<totalStates;i++){
        p_distr[i] = p_distr[i] / Z;
    }
}

// 確率を計算
void RBM::p_distr_v_calc(){
    int i,j,k;
    double Z = 0;

    // 配列の初期化
    for(i=0;i<vStates;i++){
        p_distr_v[i] = 0;
    }

    // すべての状態の確率を求める
    for(k=0;k<vStates;k++){
        // 状態を設定
        for(i=0;i<v.size();i++){
            v[i] = (k >> i)&1;
        }
        for(i=0;i<hStates;i++){
            for(j=0;j<h.size();j++){
                h[j] = (i >> j)&1;
            }
            p_distr_v[k] += exp(-energy_calc());
        }
    }

    for(i=0;i<this->vStates;i++){
        Z += p_distr_v[i];
    }

    for(i=0;i<vStates;i++){
        p_distr_v[i] = p_distr_v[i] / Z;
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
        lambda = c[j];
        for(i=0;i<v.size();i++){
            lambda += W[i][j]*v[i];
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
    for(i=0;i<vStates;i++){
        histgram_v[i] = 0;
    }
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
        histgram_v[stateV()] += 1;
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
        state += v[i] * pow(2,i);
    }
    for(i=0;i<h.size();i++){
        state += h[i] * pow(2,i+v.size());
    }
    return state;
}

// データを生成する関数
void RBM::dataGen(int num){
    int i,j;
    FILE *datafile;
    
    // ヒストグラムを初期化
    for(i=0;i<vStates;i++){
        histgram_v[i] = 0;
    }
    for(i=0;i<totalStates;i++){
        histgram[i] = 0;
    }

    // バーンイン時間
    for(i=0;i<1000;i++){
        update_v();
        update_h();
    }

    datafile = fopen("./data/data.dat", "w");

    // データ生成のループ
    for(i=0;i<num;i++){
        for(j=0;j<1;j++){
            update_v();
            update_h();
        }
        fprintf(datafile, "%d\n", stateV());
        histgram[state_num()] += 1;
        histgram_v[stateV()] += 1;
    }
    fclose(datafile);
}

// データを読み込む関数
void RBM::dataRead(int num){
    int i, j, x;
    FILE *datafile;
    traindatanum = num;
    traindata.resize(num);
    for(i=0;i<num;i++){
        traindata[i].resize(v.size());
    }
    datafile = fopen("./data/data.dat", "r");
    for(i=0;i<num;i++){
        fscanf(datafile, "%d", &x);
        setV(x);
        for(j=0;j<v.size();j++){
            traindata[i][j] = v[j];
        }
    }
    fclose(datafile);
}

void RBM::train(){

}

// 可視変数の状態を2進数で返す関数
int RBM::stateV(){
    int i;
    int num = 0;
    for(i=0;i<v.size();i++){
        num += pow(2,i)*v[i];
    }
    return num;
}

void RBM::setV(int num){
    int i;
    for(i=0;i<v.size();i++){
        v[i] = (num >> i) & 1;
    }
}