#include <stdio.h>
#include <stdlib.h>
#include "perceptron.h"

int main(int argc, char *argv[])
{
    char *fname = argv[1];
    char test[8] = "test.dat";

    // Building
    Data data = new_Data(fname);
    Model model = new_Model(data);
    //initialize_model(model); not needed since the initialize_model function has been deprecated

    // Training
    fit_model(model, data);

    // Testing
    delete_Data(data);
    Data data2 = new_Data(test);
    evaluate_model(model, data2);

    // Scoring
    run_scoring_engine(model);

    delete_Data(data2);
    delete_Model(model);

    return 0;
}
