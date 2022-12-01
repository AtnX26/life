#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "perceptron.h"

struct data {
    double **inputs;
    int *targets;
    struct shp *shape;
    
};

struct shp{
        int number_of_examples;
        int number_of_features;
};

struct model {
    double *weights;
    struct shpe *shape;
};

struct shpe{
    int dimensionality;
};

Data new_Data(const char *fname)
{
    Data data = (Data) malloc(sizeof(Data));
    data->shape = malloc(sizeof(struct shp));
    FILE *fp;
    
    if ((fp = fopen(fname, "r")) == NULL) {
 	fprintf(stderr, "load_data: can't open %s\n", fname);
        exit(1);
    }


    int numbers = 0;
    int features = 0;
    char c;
   // for (c = getc(fp); c!= EOF; c = getc(fp))
//	if (c == '\n')
  //          numbers = numbers + 1;
    numbers = 20;
    data->shape->number_of_examples = 20; //numbers;

   // double temp = 0;
   // while (fscanf(fp,"%lf",&temp) != EOF)
//	features = features + 1;
  //  features = (features/numbers); //- numbers;
    features = 2;
    data->shape->number_of_features = features;


    data->inputs = (double **)malloc(sizeof(double *) * numbers);
    int j;
    for (j = 0; j < numbers; j++){
         data->inputs[j] = (double *)malloc(sizeof(double) * features);
    }

    data->targets = (int *) malloc(numbers * sizeof(int));

    int i = 0;
    int loc = 0;
    double temp2 = 0;
    while (i<numbers){
	while (fscanf(fp, "%lf", &temp2) != EOF && loc < features){
	        data->inputs[i][loc] = temp2;
                loc = loc + 1;
        }
        fscanf(fp, "%d", &(data->targets[i]));
        i++;
        loc = 0;
        
    }


    fclose(fp);
    fprintf(stdout, "load_data: loaded %d examples\n", i);
}


Model new_Model(const Data data)
{
    Model model = (Model) malloc(sizeof(Model));
    model->shape = malloc(sizeof(struct shpe));
    int dimensions = data->shape->number_of_features + 1;
    //int dimensions = 3;
    printf("%d dimensions /n",dimensions);
    model->weights = (double*) malloc(dimensions * sizeof(double));
    for (int i = 0; i < dimensions; i++)
        model->weights[i] = (double) rand() / RAND_MAX;
    model->shape->dimensionality = dimensions;
    
    return model;
}


static void sgd(Model model, Data data)
{
    int j = 0;
    model->weights[0] += data->targets[0] * 1;
    int q = model->shape->dimensionality;
    for (j = 0; j < data->shape->number_of_features; j++){

    model->weights[q-j] += (data->targets[0]) * (data->inputs[0][j]);
   
    }
}

static int predict(Model model, Data data)
{
    double hypothesis;
    hypothesis = model->weights[0];
    int q = model->shape->dimensionality;
    for (int t = 0; t < data->shape->number_of_features; t++){
    
    hypothesis += model->weights[q-t] * data->inputs[0][t];

    }
    return (hypothesis < 0) ? -1 : 1;
}

void fit_model(Model model, Data data)
{
    double hypothesis, target;
    
    Data temp_data = (Data) malloc(sizeof(Data));
    temp_data->inputs = (double **)malloc(sizeof(double *));
    temp_data->inputs[0] = (double *)malloc(sizeof(double) * data->shape->number_of_features);
    temp_data->targets = (int *) malloc(sizeof(int));
    temp_data->shape->number_of_examples = 1;
    temp_data->shape->number_of_features = data->shape->number_of_features;

    bool misclassified = true;
    while (misclassified) {
        misclassified = false;
        for (int i = 0; i < data->shape->number_of_examples; i++) {
            for (int j = 0; j < data->shape->number_of_features; j++){
                temp_data->inputs[0][j] = data->inputs[i][j];
                }
            hypothesis = predict(model, temp_data);
            target = data->targets[i];
            if ((hypothesis > 0 && target > 0) || (hypothesis < 0 && target < 0))
                continue;
            sgd(model, temp_data);
            misclassified = true;
        }
    }
}

void run_scoring_engine(Model model)
{
    double x, y;

    printf("Enter x: \n");
    scanf("%lf", &x);

    printf("Enter y: \n");
    scanf("%lf", &y);

    Data score_data = (Data) malloc(sizeof(Data));
    score_data->inputs = (double **)malloc(sizeof(double *));
    score_data->inputs[0] = (double *)malloc(sizeof(double) * 2);
    score_data->targets = (int *)malloc(sizeof(int));
    score_data->shape->number_of_examples = 1;
    score_data->shape->number_of_features = 2;

    score_data->inputs[0][0] = x;
    score_data->inputs[0][1] = y;
    printf("Prediction = %d\n", predict(model, score_data));
}
