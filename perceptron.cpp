/**
 * An implementation of the Perceptron Learning Algorithm in C++
 *
 * Program is designed to predict low/high of median housing price
 * based on Boston housing dataset in 'boston.csv'.
 *
 * The number of training epochs is passed in through command line
 * argument at runtime.
 *
 * Expected usage is <program> <number of epochs>
 *
 * Requires boost library for Preparation Object
 * Boost can be installed on Debian/Ubuntu systems with apt-get install libboost-dev
 *
 * Written by Jonathan Pennington
 */

#include "perceptron.h"

using namespace std;

Perceptron::Perceptron() {

}

Perceptron::~Perceptron() {

}

vector<double> Perceptron::train(vector<vector<double>> trainingData,vector<double> medVs, vector<double> current_weights){
    vector<double> updated_weights=current_weights;
    int training_size=trainingData.size();

    // Train all our data, updating the weights each time
	for(int i=0;i<training_size;i++){
        updated_weights=train_step(trainingData[i],medVs[i],updated_weights);
    }
    return updated_weights;
}

vector<double> Perceptron::train_step(vector<double> x, int y, vector<double> weights) {
	vector<double> new_weights=weights;
    int y_hat;
	double delta;

    y_hat=predict(x,weights);
    delta=calc_delta(y,y_hat);
    new_weights=update_weights(weights,x,delta);

    return new_weights;
}

int Perceptron::predict(vector<double> x,vector<double> weights){
	double weighted_sum=0.0;
	int num_feats=x.size();

	// Take the Linear Weighted Sum
	for(int i=0;i<num_feats;i++){
		weighted_sum+=(x[i]*weights[i]);
	}
	if(weighted_sum>=1)
		return 1;
	else
		return 0;
}

double Perceptron::calc_delta(double y, double y_hat){
	return (y-y_hat);
}

vector<double> Perceptron::update_weights(vector<double> weights,vector<double> feats, double delta){
	vector<double> new_weights=weights;
	double bias=delta;
	int num_weights=weights.size();

	for(int i=0;i<num_weights;i++){
		new_weights[i]+=(feats[i]*delta+(bias));
	}

	return new_weights;
}
