#include "rbm.h"

int main(void){
    int n_v = 5;
    int n_h = 5;
    int num = 1000;
    RBM rbm1(n_v, n_h);
    RBM rbm2(n_v, n_h);

    FILE *f;
    int i;
    rbm1.p_distr_v_calc();
    f = fopen("./data/rbm1_p.dat", "w");
    if (f != NULL) {
        for(i=0;i<rbm1.vStates;i++){
            fprintf(f, "%d %lf\n", i, rbm1.p_distr_v[i]); // ファイルにテキストを書き込む
        }
        fclose(f); // ファイルを閉じる
    } else {
        perror("Error opening f"); // ファイルを開けなかった場合のエラー処理
        return 1;
    }

    rbm1.p_distr_calc();
    FILE *p;
    p = fopen("./data/p_distr1.dat", "w");
    if (p != NULL) {
        for(i=0;i<rbm1.totalStates;i++){
            fprintf(p, "%d %lf\n", i, rbm1.p_distr[i]); // ファイルにテキストを書き込む
        }
        fclose(p); // ファイルを閉じる
    } else {
        perror("Error opening p"); // ファイルを開けなかった場合のエラー処理
        return 1;
    }

    rbm1.dataGen(num); // 訓練データを生成
    rbm2.dataRead(num); // 訓練データを読み込む

    f = fopen("./data/rbm1_q.dat", "w");
    if (f != NULL) {
        for(i=0;i<rbm1.vStates;i++){
            fprintf(f, "%d %d\n", i, rbm1.histgram_v[i]); // ファイルにテキストを書き込む
        }
        fclose(f); // ファイルを閉じる
    } else {
        perror("Error opening f"); // ファイルを開けなかった場合のエラー処理
        return 1;
    }

    rbm2.train_sampling(300); // 訓練データを用いて学習

    rbm2.p_distr_v_calc();
    f = fopen("./data/rbm2_p.dat", "w");
    if (f != NULL) {
        for(i=0;i<rbm2.vStates;i++){
            fprintf(f, "%d %lf\n", i, rbm2.p_distr_v[i]); // ファイルにテキストを書き込む
        }
        fclose(f); // ファイルを閉じる
    } else {
        perror("Error opening f"); // ファイルを開けなかった場合のエラー処理
        return 1;
    }

    rbm2.sampling(num);
    f = fopen("./data/rbm2_q.dat", "w");
    if (f != NULL) {
        for(i=0;i<rbm2.vStates;i++){
            fprintf(f, "%d %d\n", i, rbm2.histgram_v[i]); // ファイルにテキストを書き込む
        }
        fclose(f); // ファイルを閉じる
    } else {
        perror("Error opening f"); // ファイルを開けなかった場合のエラー処理
        return 1;
    }

    rbm1.p_distr_calc();
    p = fopen("./data/p_distr1.dat", "w");
    if (p != NULL) {
        for(i=0;i<rbm1.totalStates;i++){
            fprintf(p, "%d %lf\n", i, rbm1.p_distr[i]); // ファイルにテキストを書き込む
        }
        fclose(p); // ファイルを閉じる
    } else {
        perror("Error opening p"); // ファイルを開けなかった場合のエラー処理
        return 1;
    }

    p = fopen("./data/histgram1.dat", "w");
    if (p != NULL) {
        for(i=0;i<rbm1.totalStates;i++){
            fprintf(p, "%d %lf\n", i, (double)rbm1.histgram[i]/num); // ファイルにテキストを書き込む
        }
        fclose(p); // ファイルを閉じる
    } else {
        perror("Error opening p"); // ファイルを開けなかった場合のエラー処理
        return 1;
    }

    rbm2.p_distr_calc();
    p = fopen("./data/p_distr2.dat", "w");
    if (p != NULL) {
        for(i=0;i<rbm2.totalStates;i++){
            fprintf(p, "%d %lf\n", i, rbm2.p_distr[i]); // ファイルにテキストを書き込む
        }
        fclose(p); // ファイルを閉じる
    } else {
        perror("Error opening p"); // ファイルを開けなかった場合のエラー処理
        return 1;
    }

    p = fopen("./data/histgram2.dat", "w");
    if (p != NULL) {
        for(i=0;i<rbm2.totalStates;i++){
            fprintf(p, "%d %lf\n", i, (double)rbm2.histgram[i]/num); // ファイルにテキストを書き込む
        }
        fclose(p); // ファイルを閉じる
    } else {
        perror("Error opening p"); // ファイルを開けなかった場合のエラー処理
        return 1;
    }

    return 0;
}