#include "rbm.h"
#include <stdio.h>

int main(void){
    RBM rbm(5,5);
    int num = 10000;
    cout << "start p_distr_v_calc()" << endl;
    rbm.p_distr_v_calc();
    cout << "end p_distr_v_calc()" << endl;

    rbm.sampling(num);
    printf("before paramInput\n");
    rbm.paramPrint();
    printf("\n");
    rbm.paramInput();
    printf("after paramInput\n");
    rbm.paramPrint();
    printf("\n");

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
            fprintf(p, "%d %lf\n", i, (double)rbm.histgram_v[i]/num); // ファイルにテキストを書き込む
        }
        fclose(p); // ファイルを閉じる
    } else {
        perror("Error opening p"); // ファイルを開けなかった場合のエラー処理
        return 1;
    }

    return 0;
}