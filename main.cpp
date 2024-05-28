#include "rbm.h"
#include <stdio.h>

int main(void){
    RBM rbm(5,5);
    int num = 1000;
    cout << "start p_distr_calc()" << endl;
    rbm.p_distr_calc();
    cout << "end p_distr_calc()" << endl;

    FILE *p;
    int i;
    p = fopen("./data/p_distr.dat", "w");
    if (p != NULL) {
        for(i=0;i<rbm.totalStates;i++){
            fprintf(p, "%d %lf\n", i, rbm.p_distr[i]); // ファイルにテキストを書き込む
        }
        fclose(p); // ファイルを閉じる
    } else {
        perror("Error opening p"); // ファイルを開けなかった場合のエラー処理
        return 1;
    }

    return 0;
}