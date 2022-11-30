#include <stdio.h>
#include <stdlib.h>
#include "perceptron.h"

int main(int argc, char *argv[])
{
    char *fname = argv[1];


    // Building
    Data data = new_Data(fname);

    Model model = new_Model();
    initialize_model(model);

    // Training
    fit_model(model, data);

    // Testing
    // TODO

    // Scoring
    run_scoring_engine(model);

    free(data);
    free(model);

    return 0;
}
