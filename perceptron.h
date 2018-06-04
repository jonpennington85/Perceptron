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

#ifndef PERCEPTRON_H_
#define PERCEPTRON_H_
#include <iostream>
#include <vector>

using namespace std;

class Perceptron {
public:
	Perceptron();
	virtual ~Perceptron();
	vector<double> train(vector<vector<double>> trainingData,vector<double> medVs, vector<double> weights);
	int predict(vector<double> x,vector<double> weights);
private:
	vector<double> train_step(vector<double>,int,vector<double>);
	double calc_delta(double y, double y_hat);
	vector<double> update_weights(vector<double> weights,vector<double> feats, double delta);
};

#endif /* PERCEPTRON_H_ */
