#include "rbm.h"

int main(void){
    int n_v = 5;
    int n_h = 10;
    int num = 100;
    int epoch = 1000;
    int learn_time = 10;
    int i, j, k;
    vector<double> log_likelihood_sum;
    vector<double> log_likelihood;
    FILE *file;
    RBM *gen;
    RBM *learn;

    log_likelihood_sum.resize(epoch);
    log_likelihood.resize(epoch);
    for(i=0;i<epoch;i++){
        log_likelihood_sum[i] = 0;
        log_likelihood[i] = 0;
    }

    printf("\n\n");
    for(i=0;i<learn_time;i++){
        printf("\033[2Alearn time: %d\033[0K\n", i+1);
        gen = new RBM(n_v, n_h);
        learn = new RBM(n_v, n_h);

        gen->dataGen(num);
        learn->dataRead(num);
        learn->train(epoch);

        delete gen;
        delete learn;

        file = fopen("./data/log_likelihood.dat", "r");
        if(file == NULL){
            printf("error: ./data/log_likelihood.dat\n");
            exit(1);
        }
        for(j=0;j<epoch;j++){
            fscanf(file, "%d %lf\n", &k, &log_likelihood[j]);
            log_likelihood_sum[j] += log_likelihood[j];
        }
        fclose(file);
    }

    file = fopen("./data/log-likelihood-ave.dat", "w");
    for(i=0;i<epoch;i++){
        fprintf(file, "%d %lf\n", i, log_likelihood_sum[i]/learn_time);
    }
    fclose(file);

    return 0;
}