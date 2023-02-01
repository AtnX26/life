import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Weight {
	  Double weight;
	  
	  Weight(Double w) {
		  this.weight = w;
	  }
	  
	  public void setWeight(Double w) {
		  this.weight = w;
	  }
	  
	  public Double getWeight() {
		  return weight;
	  }
	}

class Model {
	  List<Weight> weights = new ArrayList<Weight>();
	  int dimensionality = 0;

	  Model(Data data) {
	    dimensionality = data.number_of_features + 1;
	    for (int i = 0; i < dimensionality; i++) {
	      weights.add(new Weight(Math.random()));
	    }
	  }

	  void sgd(Example example) {
	    for (int i = 0; i < weights.size(); i++) {
	      Double tempw = weights.get(i).getWeight();
	      weights.get(i).setWeight (tempw + example.target * example.input.get(i));
	    }
	  }

	  void fit(Data data) {
		int h;
		Double t;
	    boolean misclassified = true;
	    while (misclassified) {
	    	misclassified = false;
	    	for (int i = 0; i<data.examples.size(); i++) 
	    	{
	    		h = predict(data.examples.get(i));
	    		t = data.examples.get(i).target;
	    		if ((h > 0 && t > 0) || (h < 0 && t < 0)) {
	    			continue;
	    		}
	    		sgd(data.examples.get(i));
	    		misclassified = true;
	    	}
	    }
	  }

	  int predict(Example example) {
	    double hypothesis = 0.0;
	    for (int i = 0; i < weights.size(); i++) {
	      hypothesis += weights.get(i).getWeight() * example.input.get(i);
	    }
	    return (hypothesis < 0) ? -1 : 1;
	  }

	  void evaluate(Data data) {
	    Double result = 0.0;
	    int hyp;
	    Double tar;
	    for (int i = 0; i<data.examples.size(); i++) {
	    	hyp = predict(data.examples.get(i));
	    	tar = data.examples.get(i).target;
	    	if ((hyp > 0 && tar > 0) || (hyp < 0 && tar < 0)) result++;
	    }
	    result = result/data.examples.size()*100;
	    System.out.println("Percentage of correct predictions: " + result.toString() + "%");
	  }

	  void runScoringEngine() {
	     Double x, y;
		 System.out.println("Enter x: ");
	     Scanner scan = new Scanner(System.in);
	     x = scan.nextDouble();
	     System.out.println("Enter y: ");
	     y = scan.nextDouble();
         Example score_data = new Example();
         score_data.input.add(1.0);
         score_data.input.add(x);
         score_data.input.add(y);
         System.out.println(String.valueOf(predict(score_data)));
	  }
    }
