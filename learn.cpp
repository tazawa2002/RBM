#include "rbm.h"

int main(void){
    int n_v = 5;
    int n_h = 5;
    int num = 1000;
    RBM rbm1(n_v, n_h);
    RBM rbm2(n_v, n_h);

    rbm1.dataGen(num); // 訓練データを生成
    rbm2.dataRead(num); // 訓練データを読み込む
    // rbm2.train(); // 群連データを用いて学習

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

    return 0;
}