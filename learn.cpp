#include "rbm.h"

int main(void){
    int n_v = 8;
    int n_h = 50;
    int num = 1000;
    int epoch = 100;
    RBM rbm1(n_v, 50);
    RBM rbm2(n_v, 10);
    rbm2.setTrainType(RBM::TrainType::sampling);
    rbm1.setAnimeteType(RBM::AnimeteType::anime);
    rbm2.setAnimeteType(RBM::AnimeteType::anime);
    rbm2.sampling_num = num;

    rbm1.dataGen(num); // 訓練データを生成
    rbm2.dataRead(num); // 訓練データを読み込む
    rbm2.trainMiniBatch(epoch, 100); // 訓練データを用いて学習
    //rbm2.train(epoch);

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