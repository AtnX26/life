class Weight {
  //TODO
}

class Model {
  List<Weight> weights = new ArrayList<Weight>();
  Double dimensionality = 0;

  Model(Data data) {
    dimensionality = data.number_of_features + 1;
    for (int i = 0; i < dimensionality; i++) {
      weights.add(new Weight(Math.random()));
    }
  }

  void sgd(Example example) {
    for (int i = 0; i < weights.size(); i++) {
      weights[i].value += example.target * example.input.get(i);
    }
  }

  void fit(Data data) {
    //TODO
  }

  int predict(Example example) {
    double hypothesis = 0.0;
    for (int i = 0; i < weights.size(); i++) {
      hypothesis += weights[i].value * example.input.get(i);
    }
    return (hypothesis < 0) ? -1 : 1;
  }

  void evaluate(Data data) {
    // Skip
  }

  void runScoringEngine() {
    // Skip
  }
}
