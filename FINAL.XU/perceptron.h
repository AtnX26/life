#ifndef PERCEPTRON_H
#define PERCEPTRON_H

typedef struct data{
    struct shp {
        int number_of_examples;
        int number_of_features;
    }shape;
    double **inputs;
    int *targets;
} *Data;

typedef struct model{
    struct shpe{
        int dimensionality;
    }shape;
    double *weights;
} *Model;

// Building
Data new_Data(const char *fname);
Model new_Model(const Data data);

// Training
void fit_model(Model model, Data data);

// Testing
void evaluate_model(Model model, Data data);

// Scoring
void run_scoring_engine(const Model model);

//Deleting
void delete_Data(Data data);
void delete_Model(Model model);
#endif
