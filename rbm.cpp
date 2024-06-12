#include "rbm.h"

// コンストラクタ
RBM::RBM(int v_num, int h_num){
    train_type = TrainType::sampling;
    gradient_type = GradientType::nomal;
    animete_type = AnimeteType::none;
    sampling_num = 100;
    paramInit(v_num, h_num); // 変数のリサイズ

    std::random_device rd;
    gen = std::mt19937(rd()); // 乱数生成器の初期化
    dis = std::uniform_real_distribution<double>(0.0, 1.0); // 0.0から1.0の範囲で乱数を生成

    // パラメータの初期化
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

double RBM::energy_v_calc(){
    int i,j;
    double lambda;
    double energy = 0;
    for(i=0;i<this->v.size();i++){
        energy -= b[i]*v[i];
    }
    for(j=0;j<this->h.size();j++){
        lambda = c[j];
        for(i=0;i<this->v.size();i++){
            lambda += W[i][j]*v[i];
        }

        // 指数関数の発散を防ぐ処理を追加
        // 1 << exp(lambda)のとき log(1+exp(lambda)) ≒ lambda
        if(lambda > 20){
            energy -= lambda;
        }else{
            energy -= log(1+exp(lambda));
        }
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
    int i, k;
    double Z = 0;

    // 配列の初期化
    for(k=0;k<vStates;k++){
        for(i=0;i<v.size();i++){
            v[i] = (k >> i) & 1;
        }
        p_distr_v[k] = exp(-energy_v_calc());
    }

    for(k=0;k<this->vStates;k++){
        Z += p_distr_v[k];
    }

    for(k=0;k<vStates;k++){
        p_distr_v[k] = p_distr_v[k] / Z;
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

    for(i=0;i<1000;i++){
        update_v();
        update_h();
    }

    for(i=0;i<num;i++){
        for(j=0;j<10;j++){
            update_v();
            update_h();
        }
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
    int i, j, k;
    FILE *datafile;
    
    // ヒストグラムを初期化
    for(i=0;i<vStates;i++){
        histgram_v[i] = 0;
    }

    // バーンイン時間
    for(i=0;i<1000;i++){
        update_v();
        update_h();
    }

    datafile = fopen("./data/data.dat", "w");

    // データ生成のループ
    for(k=0;k<num;k++){
        for(j=0;j<1;j++){
            update_v();
            update_h();
        }
        for(i=0;i<v.size();i++){
            fprintf(datafile, "%d ", v[i]);
        }
        fprintf(datafile, "\n");
        if(animete_type == AnimeteType::anime){
            histgram_v[stateV()] += 1;
        }
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
        for(i=0;i<v.size();i++){
            fscanf(datafile, "%d", &x);
            traindata[k][i] = x;
        }
    }
    fclose(datafile);
}

void RBM::train(int epoch){
    int i,j,k;
    int loop_time = 0;
    double learn_rate = 0.01;
    double gradient = 10;
    gradient_b.resize(v.size());
    gradient_c.resize(h.size());
    gradient_w.resize(v.size());
    for(i=0;i<v.size();i++){
        gradient_w[i].resize(h.size());
    }
    for(i=0;i<v.size();i++){
        gradient_b[i] = 0;
    }
    for(j=0;j<h.size();j++){
        gradient_c[j] = 0;
    }
    for(i=0;i<v.size();i++){
        for(j=0;j<h.size();j++){
            gradient_w[i][j] = 0;
        }
    }

    FILE *p = NULL;
    if(animete_type == AnimeteType::anime){
        animeInit(v.size(), h.size());
        // 対数尤度関数の出力ファイルの準備
        p = fopen("./data/log_likelihood.dat", "w");
        if(p == NULL){
            perror("Error opening log_likelihood.dat");
            exit(1);
        }
    }

    // 訓練データの期待値を計算
    data_expectation();

    std::cout << "\e[?25l"; // カーソルを非表示
    while(loop_time < epoch){
        if (train_type == TrainType::exact) {
            exact_expectation();
        } else if (train_type == TrainType::sampling) {
            sampling_expectation(sampling_num);
        }
        if(animete_type == AnimeteType::anime){
            train_anime(loop_time, 50);
            fprintf(p, "%d %lf\n", loop_time, log_likelihood());
        }

        // 勾配の計算
        if(gradient_type == GradientType::nomal){
            gradient_nomal(learn_rate);
        }else if(gradient_type == GradientType::momentum){
            gradient_momentum(learn_rate);
        }else if(gradient_type == GradientType::adagrad){
            gradient_adagrad(learn_rate);
        }else if(gradient_type == GradientType::rmsprop){
            gradient_rmsprop(learn_rate);
        }

        // パラメータの更新
        gradient = 0;
        for(i=0;i<v.size();i++){
            gradient += gradient_b[i]*gradient_b[i];
            b[i] += gradient_b[i];
        }

        for(j=0;j<h.size();j++){
            gradient += gradient_c[j]*gradient_c[j];
            c[j] += gradient_c[j];
        }

        for(i=0;i<v.size();i++){
            for(j=0;j<h.size();j++){
                gradient += gradient_w[i][j]*gradient_w[i][j];
                W[i][j] += gradient_w[i][j];
            }
        }
        gradient = sqrt(gradient);
        loop_time++;

        // 勾配を出力
        std::cout << "\r" << loop_time << ": " << gradient;
        if(loop_time%100 == 0) fflush(stdout);
    }
    std::cout << "\e[?25h" << endl; // カーソルの再表示
    fflush(p);
    fclose(p);
}

void RBM::train_anime(int loop_time, int skip){
    // アニメーション用のファイルを出力
    int i;
    char filename[100];
    FILE *p;
    p_distr_v_calc();
    if(loop_time%skip == 0){
        snprintf(filename, sizeof(filename), "./data/learn-v-%03d.dat", loop_time/skip);
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
}

void RBM::exact_expectation(){
    int i, j, k;
    double lambda;
    p_distr_v_calc();
    for(i=0;i<v.size();i++){
        // v_iのモデル平均
        Ev[i] = 0;
        for(k=0;k<vStates;k++){
            Ev[i] += p_distr_v[k]*((k>>i)&1);
        }
    }
    for(j=0;j<h.size();j++){
        // h_jのモデル平均
        Eh[j] = 0;
        for(k=0;k<vStates;k++){
            lambda = c[j];
            for(i=0;i<v.size();i++){
                lambda += W[i][j]*((k>>i)&1);
            }
            Eh[j] += p_distr_v[k]*sig(lambda);
        }
    }
    for(i=0;i<v.size();i++){
        for(j=0;j<h.size();j++){
            // vhのモデル平均
            Evh[i][j] = 0;
            for(k=0;k<vStates;k++){
                lambda = c[j];
                for(int l=0;l<v.size();l++){
                    lambda += W[l][j]*((k>>l)&1);
                }
                Evh[i][j] += ((k>>i)&1)*sig(lambda)*p_distr_v[k];
            }
        }
    }
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

void RBM::data_expectation(){
    int i, j, k;
    double lambda;
    vector<double> sig_lambda;
    sig_lambda.resize(traindatanum);

    for(i=0;i<v.size();i++){
        // v_iのデータ平均を求める処理
        Ev_data[i] = 0;
        for(k=0;k<traindatanum;k++){
            Ev_data[i] += traindata[k][i];
        }
        Ev_data[i] /= traindatanum;
    }
    for(j=0;j<h.size();j++){
        // h_iのデータ平均を求める処理
        Eh_data[j] = 0;
        for(k=0;k<traindatanum;k++){
            // lambdaを計算する
            lambda = c[j];
            for(i=0;i<v.size();i++){
                lambda += W[i][j]*traindata[k][i];
            }
            sig_lambda[k] = sig(lambda);
            Eh_data[j] += sig_lambda[k];
        }
        Eh_data[j] /= traindatanum;

        for(i=0;i<v.size();i++){
            // vhのデータ平均を求める処理
            Evh_data[i][j] = 0;
            for(k=0;k<traindatanum;k++){
                Evh_data[i][j] += traindata[k][i]*sig_lambda[k];
            }
            Evh_data[i][j] /= traindatanum;
        }
    }
}

void RBM::gradient_nomal(double learn_rate){
    int i, j;
    for(i=0;i<v.size();i++){
        gradient_b[i] = learn_rate*(Ev_data[i] - Ev[i]);
    }
    for(j=0;j<h.size();j++){
        gradient_c[j] = learn_rate*(Eh_data[j] - Eh[j]);
    }
    for(i=0;i<v.size();i++){
        for(j=0;j<h.size();j++){
            gradient_w[i][j] = learn_rate*(Evh_data[i][j] - Evh[i][j]);
        }
    }
}

void RBM::gradient_momentum(double learn_rate){
    int i, j;
    double mu = 0.8;
    for(i=0;i<v.size();i++){
        gradient_b[i] = mu*gradient_b[i] + (1-mu)*learn_rate*(Ev_data[i] - Ev[i]);
    }
    for(j=0;j<h.size();j++){
        gradient_c[j] = mu*gradient_c[j] + (1-mu)*learn_rate*(Eh_data[j] - Eh[j]);
    }
    for(i=0;i<v.size();i++){
        for(j=0;j<h.size();j++){
            gradient_w[i][j] = mu*gradient_w[i][j] + (1-mu)*learn_rate*(Evh_data[i][j] - Evh[i][j]);
        }
    }
}

void RBM::gradient_adagrad(double learn_rate){
    int i, j;
    double epsilon = 1e-8; // ゼロ除算を防ぐための小さな値
    static vector<double> gradient_b_sum;
    static vector<double> gradient_c_sum;
    static vector<vector<double>> gradient_w_sum;

    // 勾配の二乗和を保持する配列が未定義の場合は初期化する
    if (gradient_b_sum.empty()) {
        gradient_b_sum.resize(v.size(), 0.0);
        gradient_c_sum.resize(h.size(), 0.0);
        gradient_w_sum.resize(v.size(), std::vector<double>(h.size(), 0.0));
    }

    for(i=0;i<v.size();i++){
        double grad_b = Ev_data[i] - Ev[i];
        gradient_b_sum[i] += grad_b * grad_b;
        gradient_b[i] = (learn_rate / sqrt(gradient_b_sum[i] + epsilon)) * grad_b;
    }
    for(j=0;j<h.size();j++){
        double grad_c = Eh_data[j] - Eh[j];
        gradient_c_sum[j] += grad_c * grad_c;
        gradient_c[j] = (learn_rate / sqrt(gradient_c_sum[j] + epsilon)) * grad_c;
    }
    for(i=0;i<v.size();i++){
        for(j=0;j<h.size();j++){
            double grad_w = Evh_data[i][j] - Evh[i][j];
            gradient_w_sum[i][j] += grad_w * grad_w;
            gradient_w[i][j] = (learn_rate / sqrt(gradient_w_sum[i][j] + epsilon)) * grad_w;
        }
    }
}

void RBM::gradient_rmsprop(double learn_rate){
    int i, j;
    double epsilon = 1e-8; // ゼロ除算を防ぐための小さな値
    double rho = 0.9;
    static vector<double> gradient_b_v;
    static vector<double> gradient_c_v;
    static vector<vector<double>> gradient_w_v;

    // 勾配の二乗和を保持する配列が未定義の場合は初期化する
    if (gradient_b_v.empty()) {
        gradient_b_v.resize(v.size(), 0.0);
        gradient_c_v.resize(h.size(), 0.0);
        gradient_w_v.resize(v.size(), std::vector<double>(h.size(), 0.0));
    }

    for(i=0;i<v.size();i++){
        double grad_b = Ev_data[i] - Ev[i];
        gradient_b_v[i] = rho*gradient_b_v[i] + (1-rho)*grad_b*grad_b;
        gradient_b[i] = (learn_rate / sqrt(gradient_b_v[i] + epsilon)) * grad_b;
    }
    for(j=0;j<h.size();j++){
        double grad_c = Eh_data[j] - Eh[j];
        gradient_c_v[j] = rho*gradient_c_v[j] + (1-rho)*grad_c*grad_c;
        gradient_c[j] = (learn_rate / sqrt(gradient_c_v[j] + epsilon)) * grad_c;
    }
    for(i=0;i<v.size();i++){
        for(j=0;j<h.size();j++){
            double grad_w = Evh_data[i][j] - Evh[i][j];
            gradient_w_v[i][j] = rho*gradient_w_v[i][j] + (1-rho)*grad_w*grad_w;
            gradient_w[i][j] = (learn_rate / sqrt(gradient_w_v[i][j] + epsilon)) * grad_w;
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

void RBM::paramOutput(){
    int i, j;
    FILE *p;
    p = fopen("./data/param.dat", "w");
    if (p == NULL) {
        perror("Error opening p");
        return;
    }

    // 可視変数の数と隠れ変数の数を出力
    fprintf(p, "%ld %ld\n", v.size(), h.size());

    // パラメータbの出力
    for(i=0;i<v.size();i++){
        fprintf(p, "%lf ", b[i]);
    }
    fprintf(p, "\n");

    // パラメータcの出力
    for(j=0;j<h.size();j++){
        fprintf(p, "%lf ", c[j]);
    }
    fprintf(p, "\n");

    // パラメータWの出力
    for(i=0;i<v.size();i++){
        for(j=0;j<h.size();j++){
            fprintf(p, "%lf ", W[i][j]);
        }
        fprintf(p, "\n");
    }
    fclose(p);
}

void RBM::paramInput(){
    int i, j;
    int v_num, h_num;
    FILE *p;
    p = fopen("./data/param.dat", "r");
    if (p == NULL) {
        perror("Error opening p");
        return;
    }

    // 可視変数の数と隠れ変数の数を入力
    fscanf(p, "%d %d", &v_num, &h_num);
    paramInit(v_num, h_num);

    // パラメータbの入力
    for(i=0;i<v.size();i++){
        fscanf(p, "%lf", &b[i]);
    }

    // パラメータcの入力
    for(j=0;j<h.size();j++){
        fscanf(p, "%lf", &c[j]);
    }

    // パラメータWの入力
    for(i=0;i<v.size();i++){
        for(j=0;j<h.size();j++){
            fscanf(p, "%lf", &W[i][j]);
        }
    }
    fclose(p);
}

void RBM::paramPrint(){
    int i, j;
    for(i=0;i<v.size();i++){
        printf("%lf ", b[i]);
    }
    printf("\n");

    for(j=0;j<h.size();j++){
        printf("%lf ", c[j]);
    }
    printf("\n");

    for(i=0;i<v.size();i++){
        for(j=0;j<h.size();j++){
            printf("%lf ", W[i][j]);
        }
        printf("\n");
    }
}

void RBM::paramInit(int v_num, int h_num){
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
    this->Ev_data.resize(v_num);
    this->Eh_data.resize(h_num);
    this->Evh_data.resize(v_num);
    for(int i=0;i<v_num;i++){
        this->Evh_data[i].resize(h_num);
    }

    // 厳密計算とアニメーションに必要な変数
    if(train_type == TrainType::exact || animete_type == AnimeteType::anime){
        animeInit(v_num, h_num);
    }
}

void RBM::animeInit(int v_num, int h_num){
    this->vStates = pow(2,v_num);
    this->hStates = pow(2,h_num);
    this->p_distr_v.resize(this->vStates);
    this->histgram_v.resize(this->vStates);
}

void RBM::setAnimeteType(AnimeteType type){
    this->animete_type = type;
    if(animete_type == AnimeteType::anime){
        animeInit(v.size(), h.size());
    }
}

void RBM::setTrainType(TrainType type){
    this->train_type = type;
    if(train_type == TrainType::exact){
        animeInit(v.size(), h.size());
    }
}

void RBM::setGradientType(GradientType type){
    this->gradient_type = type;
}

void RBM::setSamplingNum(int num){
    this->sampling_num = num;
}

double RBM::log_likelihood(){
    int i, mu;
    int state;
    double lambda;
    double log_likelihood = 0;
    for(mu=0;mu<traindatanum;mu++){
        state = 0;
        for(i=0;i<v.size();i++){
            state += traindata[mu][i]*pow(2,i);
        }
        log_likelihood += log(p_distr_v[state]);
    }
    return log_likelihood / traindatanum;
}