#include "rbm.h"

int main(void){
    int n_v = 5;
    int n_h = 10;
    int num = 100;
    int epoch = 200;
    int learn_time = 1000;
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
        gen->setAnimeteType(RBM::AnimeteType::none);
        learn->setAnimeteType(RBM::AnimeteType::none);
        learn->setTrainType(RBM::TrainType::exact);
        learn->setGradientType(RBM::GradientType::nomal);

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

    file = fopen("./data/log-likelihood-ave-nomal.dat", "w");
    for(i=0;i<epoch;i++){
        fprintf(file, "%d %lf\n", i, log_likelihood_sum[i]/learn_time);
    }
    fclose(file);

    for(i=0;i<epoch;i++){
        log_likelihood_sum[i] = 0;
        log_likelihood[i] = 0;
    }

    for(i=0;i<learn_time;i++){
        printf("\033[2Alearn time: %d\033[0K\n", i+1);
        gen = new RBM(n_v, n_h);
        learn = new RBM(n_v, n_h);
        gen->setTrainType(RBM::TrainType::exact);
        learn->setAnimeteType(RBM::AnimeteType::none);
        learn->setTrainType(RBM::TrainType::exact);
        learn->setSamplingNum(num);
        learn->setGradientType(RBM::GradientType::momentum);

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

    file = fopen("./data/log-likelihood-ave-momentum.dat", "w");
    for(i=0;i<epoch;i++){
        fprintf(file, "%d %lf\n", i, log_likelihood_sum[i]/learn_time);
    }
    fclose(file);

    for(i=0;i<epoch;i++){
        log_likelihood_sum[i] = 0;
        log_likelihood[i] = 0;
    }

    for(i=0;i<learn_time;i++){
        printf("\033[2Alearn time: %d\033[0K\n", i+1);
        gen = new RBM(n_v, n_h);
        learn = new RBM(n_v, n_h);
        gen->setTrainType(RBM::TrainType::exact);
        learn->setAnimeteType(RBM::AnimeteType::none);
        learn->setTrainType(RBM::TrainType::exact);
        learn->setSamplingNum(num);
        learn->setGradientType(RBM::GradientType::adagrad);

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

    file = fopen("./data/log-likelihood-ave-adagrad.dat", "w");
    for(i=0;i<epoch;i++){
        fprintf(file, "%d %lf\n", i, log_likelihood_sum[i]/learn_time);
    }
    fclose(file);

    return 0;
}