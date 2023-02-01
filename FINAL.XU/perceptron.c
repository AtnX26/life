#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "perceptron.h"


Data new_Data(const char *fname)
{
    Data data = (Data) malloc(sizeof(*data));
    FILE *fp;
    
    if ((fp = fopen(fname, "r")) == NULL) {
 	fprintf(stderr, "load_data: can't open %s\n", fname);
        exit(1);
    }

    //read numbers of examples by counting the lines in the file
    int numbers = 0;
    int features = 0;
    char c;
    for (c = getc(fp); c!= EOF; c = getc(fp))
	{if (c == '\n')
            numbers = numbers + 1;}
    data->shape.number_of_examples = numbers;
    //close and reopen the file to set the pointer fp back to the starting location
    fclose(fp);
    fp = fopen(fname, "r");

    //read numbers of features by counting the doubles in the file
    double temp = 0;
    while (fscanf(fp,"%lf",&temp) != EOF)
        features = features + 1;
    features = (features-numbers)/numbers;
    data->shape.number_of_features = features;
    
    
    fclose(fp);
    fp = fopen(fname, "r");
    
    
    //dynamically allocate memory for the Data instance using the shape information
    data->inputs = (double **)malloc(sizeof(double *) * numbers);
    int j;
    for (j = 0; j < numbers; j++){
         data->inputs[j] = (double *)malloc(sizeof(double) * features);
    }

    data->targets = (int *) malloc(numbers * sizeof(int));

    //read data in the file, put everything but the last item of each line into inputs and put the last item of each line into targets
    int i = 0;
    int loc = 0;
    double temp2 = 0;
    while (i<numbers){
	while (loc < features){
	        fscanf(fp, "%lf",&temp2);
                data->inputs[i][loc] = temp2;
                loc = loc + 1;
        }
        double a = 0;
        fscanf(fp, "%lf", &a);
        data->targets[i] = (int) a;
        i++;
        loc = 0;
        
    }


    fclose(fp);
    fprintf(stdout, "load_data: loaded %d examples\n", data->shape.number_of_examples);
    return data;
}


//initialize a model with information from the Data parameter
Model new_Model(const Data data)
{
    Model model = (Model) malloc(sizeof(*model));
    int dimensions = data->shape.number_of_features + 1;
    model->weights = (double*) malloc(dimensions * sizeof(double));
    for (int i = 0; i < dimensions; i++)
        model->weights[i] = (double) rand() / RAND_MAX;
    model->shape.dimensionality = dimensions; 
    return model;
}


static void sgd(Model model, Data data)
{
    int j = 0;
    model->weights[0] += data->targets[0] * 1;
    int q = (model->shape.dimensionality)-1;
    for (j = 0; j < data->shape.number_of_features; j++){

    model->weights[q-j] += (data->targets[0]) * (data->inputs[0][j]);
   
    }
}

static int predict(Model model, Data data)
{
    double hypothesis;
    hypothesis = model->weights[0];
    int q = (model->shape.dimensionality)-1;
    int t = 0;
    for (t = 0; t < data->shape.number_of_features; t++){
    
    hypothesis += model->weights[q-t] * data->inputs[0][t];

    }
    return (hypothesis < 0) ? -1 : 1;
}

void fit_model(Model model, Data data)
{
    double hypothesis, target;
    //allocate memory for a new Data instance that holds data for the current line in the for loop
    Data temp_data = (Data) malloc(sizeof(*temp_data));
    temp_data->inputs = (double **)malloc(sizeof(double *));
    temp_data->inputs[0] = (double *)malloc(sizeof(double) * data->shape.number_of_features);
    temp_data->targets = (int *) malloc(sizeof(int));
    temp_data->shape.number_of_examples = 1;
    temp_data->shape.number_of_features = data->shape.number_of_features;


    bool misclassified = true;
    while (misclassified) {
       misclassified = false;
       for (int i = 0; i < data->shape.number_of_examples; i++){
            for (int j = 0; j < data->shape.number_of_features; j++){
                temp_data->inputs[0][j] = data->inputs[i][j];
                }
            temp_data->targets[0] = data->targets[i];
            hypothesis = predict(model, temp_data);
            target = data->targets[i];
            if ((hypothesis > 0 && target > 0) || (hypothesis < 0 && target < 0))
                continue;
            sgd(model, temp_data);
            misclassified = true;
        }
    }
    delete_Data(temp_data);
}

void evaluate_model(Model model, Data data)
{
    Data temp_data = (Data) malloc(sizeof(*temp_data));
    temp_data->inputs = (double **)malloc(sizeof(double *));
    temp_data->inputs[0] = (double *)malloc(sizeof(double) * data->shape.number_of_features);
    temp_data->targets = (int *) malloc(sizeof(int));
    temp_data->shape.number_of_examples = 1;
    temp_data->shape.number_of_features = data->shape.number_of_features;
    int i, j;
    double hypothesis, target;
    double result = 0;
    for (i = 0; i < data->shape.number_of_examples; i++){
        for (j = 0; j < data->shape.number_of_features; j++){
            temp_data->inputs[0][j] = data->inputs[i][j];
            }
        temp_data->targets[0] = data->targets[i];
        hypothesis = predict(model, temp_data);
        target = data->targets[i];
        if (hypothesis == target) result++;
        }
    result = result/data->shape.number_of_examples * 100;
    fprintf(stdout,"Percentage of correct predictions: %f%%\n", result);
    delete_Data(temp_data);
}

void run_scoring_engine(Model model)
{
    double x, y;

    printf("Enter x: \n");
    scanf("%lf", &x);

    printf("Enter y: \n");
    scanf("%lf", &y);
    
    //allocate memory for a new Data instance that holds data for user inputs and is passed to the predict function
    Data score_data = (Data) malloc(sizeof(*score_data));
    score_data->inputs = (double **)malloc(sizeof(double *));
    score_data->inputs[0] = (double *)malloc(sizeof(double) * 2);
    score_data->targets = (int *)malloc(sizeof(int));
    score_data->shape.number_of_examples = 1;
    score_data->shape.number_of_features = 2;

    score_data->inputs[0][0] = x;
    score_data->inputs[0][1] = y;
    printf("Prediction = %d\n", predict(model, score_data));
    delete_Data(score_data);
}

void delete_Data(Data data)
{
    int e = data->shape.number_of_examples;
    int n = data->shape.number_of_features;
    int j;
    for (j = 0; j < e; j++){
        free(data->inputs[j]);
    }
    free(data->inputs);
    free(data->targets);
    free(data);
}

void delete_Model(Model model)
{
    free(model->weights);
    free(model);
}
