class Client {
  public static void main(String[] args) {
    // usage: java Client train.dat test.dat
    String train_dat = argv[0];
    String test_dat = argv[1];
  
    // Building
    Data training_data = new Data(train_dat);
    Data testing_data = new Data(test_dat);
    Model model = new Model(training_data);
  
    // Training
    model.fit(training_data);
  
    // Testing
    model.evaluate(testing_data);
  
    // Scoring
    model.runScoringEngine();
  }
}
