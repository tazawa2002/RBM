#include "rbm.h"

void runLearning(int learn_time, const char* filename, RBM::GradientType gradient_type, RBM::TrainType train_type, int n_v, int n_h, int num, int epoch) {
    RBM *gen;
    RBM *learn;
    vector<double> log_likelihood_sum(epoch, 0);

    for(int i = 0; i < learn_time; i++) {
        printf("\033[2Alearn time(%s): %d\033[0K\n", filename, i + 1);
        gen = new RBM(n_v, n_h);
        learn = new RBM(n_v, n_h);
        gen->setAnimeteType(RBM::AnimeteType::loglikelihood);
        learn->setAnimeteType(RBM::AnimeteType::loglikelihood);
        learn->setTrainType(train_type);
        learn->setGradientType(gradient_type);

        gen->dataGen(num);
        learn->dataRead(num);
        learn->train(epoch);

        for(int j = 0; j < learn->loglikelihood.size(); j++) {
            log_likelihood_sum[j] += learn->loglikelihood[j];
        }

        delete gen;
        delete learn;
    }

    FILE *output_file = fopen(filename, "w");
    for(int i = 0; i < epoch; i++) {
        fprintf(output_file, "%d %lf\n", i, log_likelihood_sum[i] / learn_time);
    }
    fclose(output_file);
}

int main(void) {
    int n_v = 10;
    int n_h = 10;
    int num = 1000;
    int epoch = 100;
    int learn_time = 100;
    RBM::TrainType type = RBM::TrainType::exact;
    
    // GradientTypeとその対応するファイル名の配列を定義
    vector<tuple<RBM::GradientType, RBM::TrainType, const char*>> gradient_types = {
        {RBM::GradientType::nomal, RBM::TrainType::exact, "./data/log-likelihood-ave-nomal-exact.dat"},
        {RBM::GradientType::momentum, RBM::TrainType::exact, "./data/log-likelihood-ave-momentum-exact.dat"},
        {RBM::GradientType::adagrad, RBM::TrainType::exact, "./data/log-likelihood-ave-adagrad-exact.dat"},
        {RBM::GradientType::rmsprop, RBM::TrainType::exact, "./data/log-likelihood-ave-rmsprop-exact.dat"},
        {RBM::GradientType::adadelta, RBM::TrainType::exact, "./data/log-likelihood-ave-adadelta-exact.dat"},
        {RBM::GradientType::adam, RBM::TrainType::exact, "./data/log-likelihood-ave-adam-exact.dat"},
        {RBM::GradientType::nomal, RBM::TrainType::sampling, "./data/log-likelihood-ave-nomal-sampling.dat"},
        {RBM::GradientType::momentum, RBM::TrainType::sampling, "./data/log-likelihood-ave-momentum-sampling.dat"},
        {RBM::GradientType::adagrad, RBM::TrainType::sampling, "./data/log-likelihood-ave-adagrad-sampling.dat"},
        {RBM::GradientType::rmsprop, RBM::TrainType::sampling, "./data/log-likelihood-ave-rmsprop-sampling.dat"},
        {RBM::GradientType::adadelta, RBM::TrainType::sampling, "./data/log-likelihood-ave-adadelta-sampling.dat"},
        {RBM::GradientType::adam, RBM::TrainType::sampling, "./data/log-likelihood-ave-adam-sampling.dat"}
    };

    printf("\n\n");

    for (const auto& [gradient_type, train_type, filename] : gradient_types) {
        runLearning(learn_time, filename, gradient_type, train_type, n_v, n_h, num, epoch);
    }

    return 0;
}