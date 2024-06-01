#include "rbm.h"

// コンストラクタ
RBM::RBM(int v_num, int h_num){
    // 変数の用意
    this->v.resize(v_num);
    this->h.resize(h_num);
    this->W.resize(v_num);
    for(int i=0;i<v_num;i++){
        this->W[i].resize(h_num);
    }
    this->b.resize(v_num);
    this->c.resize(h_num);
    this->Ev.resize(v_num);
    this->Eh.resize(h_num);
    this->Evh.resize(v_num);
    for(int i=0;i<v_num;i++){
        this->Evh[i].resize(h_num);
    }

    // 厳密計算に必要な変数
    this->vStates = pow(2,v_num);
    this->hStates = pow(2,h_num);
    this->totalStates = this->vStates*this->hStates;
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
    int i, k, x;
    FILE *datafile;
    traindatanum = num;
    traindata.resize(traindatanum);
    for(i=0;i<traindatanum;i++){
        traindata[i].resize(v.size());
    }
    datafile = fopen("./data/data.dat", "r");
    for(k=0;k<traindatanum;k++){
        fscanf(datafile, "%d", &x);
        setV(x);
        for(i=0;i<v.size();i++){
            traindata[k][i] = v[i];
        }
    }
    fclose(datafile);
}

void RBM::train(){
    int i,j,k;
    int loop_time = 0;
    double learn_rate = 0.01;
    double lambda;
    double v_ave_model;
    double v_ave_data;
    double h_ave_model;
    double h_ave_data;
    double vh_ave_model;
    double vh_ave_data;
    double gradient = 10;
    vector<double> gradient_b;
    vector<double> gradient_c;
    vector<vector<double> > gradient_w;
    gradient_b.resize(v.size());
    gradient_c.resize(h.size());
    gradient_w.resize(v.size());
    for(i=0;i<v.size();i++){
        gradient_w[i].resize(h.size());
    }

    // アニメーション用の変数
    FILE *p;
    char filename[100];

    std::cout << "\e[?25l"; // カーソルを非表示
    p_distr_calc();
    while(gradient>0.01){

        // パラメータの更新
        for(i=0;i<v.size();i++){

            // v_iのデータ平均を求める処理
            v_ave_data = 0;
            for(k=0;k<traindatanum;k++){
                v_ave_data += traindata[k][i];
            }
            v_ave_data /= traindatanum;

            // v_iのモデル平均
            v_ave_model = 0;
            for(k=0;k<totalStates;k++){
                v_ave_model += p_distr[k]*((k>>i)&1);
            }
            gradient_b[i] = v_ave_data - v_ave_model;
        }

        for(j=0;j<h.size();j++){
            // h_iのデータ平均を求める処理
            h_ave_data = 0;
            for(k=0;k<traindatanum;k++){
                // lambdaを計算する
                lambda = c[j];
                for(i=0;i<v.size();i++){
                    lambda += W[i][j]*traindata[k][i];
                }
                h_ave_data += sig(lambda);
            }
            h_ave_data /= traindatanum;

            // h_jのモデル平均
            h_ave_model = 0;
            for(k=0;k<totalStates;k++){
                h_ave_model += p_distr[k]*((k>>(j+v.size()))&1);
            }
            gradient_c[j] = h_ave_data - h_ave_model;
        }

        for(i=0;i<v.size();i++){
            for(j=0;j<h.size();j++){
                // vhのデータ平均を求める処理
                vh_ave_data = 0;
                for(k=0;k<traindatanum;k++){
                    lambda = c[j];
                    for(int l=0;l<v.size();l++){
                        lambda += W[l][j]*traindata[k][l];
                    }
                    vh_ave_data += traindata[k][i]*sig(lambda);
                }
                vh_ave_data /= traindatanum;

                // vhのモデル平均
                vh_ave_model = 0;
                for(k=0;k<totalStates;k++){
                    vh_ave_model += p_distr[k]*((k>>i)&1)*((k>>(j+v.size()))&1);
                }
                gradient_w[i][j] = vh_ave_data - vh_ave_model;
            }
        }

        // パラメータの更新と勾配の計算
        gradient = 0;
        for(i=0;i<v.size();i++){
            gradient += gradient_b[i]*gradient_b[i];
            b[i] += learn_rate*gradient_b[i];
        }
        for(j=0;j<h.size();j++){
            gradient += gradient_c[j]*gradient_c[j];
            c[j] += learn_rate*gradient_c[j];
        }
        for(i=0;i<v.size();i++){
            for(j=0;j<h.size();j++){
                gradient += gradient_w[i][j]*gradient_w[i][j];
                W[i][j] += learn_rate*gradient_w[i][j];
            }
        }
        gradient = sqrt(gradient);
        std::cout << "\r" << loop_time << ": " << gradient;
        if(loop_time%100 == 0) fflush(stdout);
        p_distr_calc();
        p_distr_v_calc();

        // アニメーション用のファイルを出力
        if(loop_time%10 == 0){
            sprintf(filename, "./data/learn-vh-%03d.txt", loop_time/10);
            p = fopen(filename, "w");
            if (p != NULL) {
                for(i=0;i<totalStates;i++){
                    fprintf(p, "%d %lf\n", i, p_distr[i]); 
                }
                fclose(p);
            } else {
                perror("Error opening p");
            }

            sprintf(filename, "./data/learn-v-%03d.txt", loop_time/10);
            p = fopen(filename, "w");
            if (p != NULL) {
                for(i=0;i<vStates;i++){
                    fprintf(p, "%d %lf\n", i, p_distr_v[i]);
                }
                fclose(p);
            } else {
                perror("Error opening p");
            }
        }
        loop_time++;
    }
    std::cout << "\e[?25h" << endl; // カーソルの再表示
}

void RBM::train_sampling(int num){
    int i,j,k;
    int loop_time = 0;
    double learn_rate = 0.01;
    double lambda;
    double v_ave_model;
    double v_ave_data;
    double h_ave_model;
    double h_ave_data;
    double vh_ave_model;
    double vh_ave_data;
    double gradient = 10;
    vector<double> gradient_b;
    vector<double> gradient_c;
    vector<vector<double> > gradient_w;
    gradient_b.resize(v.size());
    gradient_c.resize(h.size());
    gradient_w.resize(v.size());
    for(i=0;i<v.size();i++){
        gradient_w[i].resize(h.size());
    }

    // アニメーション用の変数
    FILE *p;
    char filename[100];

    std::cout << "\e[?25l"; // カーソルを非表示
    sampling_expectation(num);
    while(gradient>0.1){

        // パラメータの更新
        for(i=0;i<v.size();i++){

            // v_iのデータ平均を求める処理
            v_ave_data = 0;
            for(k=0;k<traindatanum;k++){
                v_ave_data += traindata[k][i];
            }
            v_ave_data /= traindatanum;

            // v_iのモデル平均
            v_ave_model = Ev[i];
            gradient_b[i] = v_ave_data - v_ave_model;
        }

        for(j=0;j<h.size();j++){
            // h_iのデータ平均を求める処理
            h_ave_data = 0;
            for(k=0;k<traindatanum;k++){
                // lambdaを計算する
                lambda = c[j];
                for(i=0;i<v.size();i++){
                    lambda += W[i][j]*traindata[k][i];
                }
                h_ave_data += sig(lambda);
            }
            h_ave_data /= traindatanum;

            // h_jのモデル平均
            h_ave_model = Eh[j];
            gradient_c[j] = h_ave_data - h_ave_model;
        }

        for(i=0;i<v.size();i++){
            for(j=0;j<h.size();j++){
                // vhのデータ平均を求める処理
                vh_ave_data = 0;
                for(k=0;k<traindatanum;k++){
                    lambda = c[j];
                    for(int l=0;l<v.size();l++){
                        lambda += W[l][j]*traindata[k][l];
                    }
                    vh_ave_data += traindata[k][i]*sig(lambda);
                }
                vh_ave_data /= traindatanum;

                // vhのモデル平均
                vh_ave_model = Evh[i][j];
                gradient_w[i][j] = vh_ave_data - vh_ave_model;
            }
        }

        // パラメータの更新と勾配の計算
        gradient = 0;
        for(i=0;i<v.size();i++){
            gradient += gradient_b[i]*gradient_b[i];
            b[i] += learn_rate*gradient_b[i];
        }
        for(j=0;j<h.size();j++){
            gradient += gradient_c[j]*gradient_c[j];
            c[j] += learn_rate*gradient_c[j];
        }
        for(i=0;i<v.size();i++){
            for(j=0;j<h.size();j++){
                gradient += gradient_w[i][j]*gradient_w[i][j];
                W[i][j] += learn_rate*gradient_w[i][j];
            }
        }
        gradient = sqrt(gradient);
        std::cout << "\r" << loop_time << ": " << gradient;
        if(loop_time%100 == 0) fflush(stdout);
        sampling_expectation(num);

        p_distr_calc();
        p_distr_v_calc();
        // アニメーション用のファイルを出力
        if(loop_time%10 == 0){
            sprintf(filename, "./data/learn-vh-%03d.txt", loop_time/10);
            p = fopen(filename, "w");
            if (p != NULL) {
                for(i=0;i<totalStates;i++){
                    fprintf(p, "%d %lf\n", i, p_distr[i]); 
                }
                fclose(p);
            } else {
                perror("Error opening p");
            }

            sprintf(filename, "./data/learn-v-%03d.txt", loop_time/10);
            p = fopen(filename, "w");
            if (p != NULL) {
                for(i=0;i<vStates;i++){
                    fprintf(p, "%d %lf\n", i, p_distr_v[i]);
                }
                fclose(p);
            } else {
                perror("Error opening p");
            }
        }
        loop_time++;
    }
    std::cout << "\e[?25h" << endl; // カーソルの再表示
}

void RBM::sampling_expectation(int num){
    int i, j, k, l;
    
    for(i=0;i<v.size();i++){
        Ev[i] = 0;
    }
    for(j=0;j<h.size();j++){
        Eh[j] = 0;
    }
    for(i=0;i<v.size();i++){
        for(j=0;j<h.size();j++){
            Evh[i][j] = 0;
        }
    }

    for(k=0;k<1000;k++){
        update_v();
        update_h();
    }

    for(k=0;k<num;k++){
        for(l=0;l<10;l++) {
            update_v();
            update_h();
        }
        
        // 期待値を足す
        for(i=0;i<v.size();i++){
            Ev[i] += v[i];
        }
        for(j=0;j<h.size();j++){
            Eh[j] += h[j];
        }
        for(i=0;i<v.size();i++){
            for(j=0;j<h.size();j++){
                Evh[i][j] += v[i]*h[j];
            }
        }
    }

    // データ数で割る
    for(i=0;i<v.size();i++){
        Ev[i] /= num;
    }
    for(j=0;j<h.size();j++){
        Eh[j] /= num;
    }
    for(i=0;i<v.size();i++){
        for(j=0;j<h.size();j++){
            Evh[i][j] /= num;
        }
    }
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