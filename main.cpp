#include "rbm.h"
#include <stdio.h>

int main(void){
    RBM rbm(5,30);
    rbm.setTrainType(RBM::TrainType::exact);
    rbm.setAnimeteType(RBM::AnimeteType::anime);
    rbm.setAnimeteType(RBM::AnimeteType::anime);
    int num = 10000;
    rbm.p_distr_v_calc();

    rbm.sampling(num);

    FILE *p;
    int i;
    p = fopen("./data/p_distr.dat", "w");
    if (p != NULL) {
        for(i=0;i<rbm.vStates;i++){
            fprintf(p, "%d %lf\n", i, rbm.p_distr_v[i]); // ファイルにテキストを書き込む
        }
        fclose(p); // ファイルを閉じる
    } else {
        perror("Error opening p"); // ファイルを開けなかった場合のエラー処理
        return 1;
    }

    p = fopen("./data/histgram.dat", "w");
    if (p != NULL) {
        for(i=0;i<rbm.vStates;i++){
            fprintf(p, "%d %lf\n", i, (double)rbm.histgram_v[i]); // ファイルにテキストを書き込む
        }
        fclose(p); // ファイルを閉じる
    } else {
        perror("Error opening p"); // ファイルを開けなかった場合のエラー処理
        return 1;
    }

    return 0;
}