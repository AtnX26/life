#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "perceptron.h"

struct data {
    double **inputs;
    int *targets;
    struct shape {
        int number_of_examples;
        int number_of_features;
    };
    
};

struct model {
    double *weights;
    struct shape {
        int dimensionality;
    };
};

Data new_Data(const char *fname)
{
    Data data = (Data) malloc(sizeof(Data));
    FILE *fp;
    
    if ((fp = fopen(fname, "r")) == NULL) {
 	fprintf(stderr, "load_data: can't open %s\n", fname);
        exit(1);
    }

    int numbers = 0;
    int features = 0;
    char c;
    for (c = getc(fp); c!= EOF; c = getc(fp))
	if (c == '\n')
            numbers = numbers + 1;
    data.shape.number_of_examples = numbers;
    double temp = 0;
    while (fscanf(fp,"%lf",&temp) != EOF)
	features = features + 1;
    features = features/numbers - numbers;
    data.shape.number_of_features = features;

    data->inputs = (double **)malloc(sizeof(double *) * data.shape.number_of_examples);
    for (i=0; i < data.shape.number_of_examples; i++){
         data->inputs[i] = (double *)malloc(sizeof(double) * data.shape.number_of_features);
    }
    data->targets = (double *) malloc(data.shape.number_of_examples * sizeof(double));

    int i = 0;
    int loc = 0;
    double temp2 = 0
    while (i<data.shape.number_of_exapmles){
	while (fscanf(fp, "%lf", &temp2) != EOF && loc < features - 1){
	        data.inputs[i][loc] = temp2;
                loc = loc + 1;
        }
	fscanf(fp, "%lf", data->targets[i]);
        i++;
        loc = 0;
        
    }
    fclose(fp);

    fprintf(stdout, "load_data: loaded %d examples\n", i);

}


Model new_Model(const Data data)
{
    Model model = (Model) malloc(sizeof(Model));
    int DIMENSIONS = data.shape.numbers_of_examples;
    model->weights = (double*) malloc(DIMENSIONS * sizeof(double));
    for (int i = 0; i < DIMENSIONS; i++)
        model->weights[i] = (double) rand() / RAND_MAX;
    return model;
}


static void sgd(Model model, Data data)
{
    model->weights[2] += target * xcoord;
    model->weights[1] += target * ycoord;
    //weights[0] = weights[0];
    model->weights[0] += target * 1;
}

static int predict(Model model, Data data)
{
    double hypothesis = model->weights[2] * xcoord + model->weights[1] * ycoord + model->weights[0];
    return (hypothesis < 0) ? -1 : 1;
}

void fit_model(Model model, Data data)
{
    double hypothesis, target;

    bool misclassified = true;
    while (misclassified) {
        misclassified = false;
        for (int i = 0; i < number_of_examples; i++) {
            hypothesis = predict(model, xcoords->elements[i], ycoords->elements[i]);
            target = targets->elements[i];
            if ((hypothesis > 0 && target > 0) || (hypothesis < 0 && target < 0))
                continue;
            sgd(model, xcoords->elements[i], ycoords->elements[i], target);
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

    printf("Prediction = %d\n", predict(model, data));
}
