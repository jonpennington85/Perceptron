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

#ifndef PREPARATION_H_
#define PREPARATION_H_

#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#define FILENAME "./boston.csv"
#define MEDV_LOC 13


using namespace std;



class Preparation {
public:
	Preparation();
	virtual ~Preparation();

	vector<vector<double>> processCSV(string);
	vector<vector<double>> separateTrain(vector<vector<double>>);
	vector<vector<double>> separateTest(vector<vector<double>>);
	vector<double> gatherMedVs(vector<vector<double>>);
	vector<vector<double>> dropMedVs(vector<vector<double>>);
	long getRandomLong();

private:

	vector<vector<double>> replaceMedv(vector<vector<double>>,double);
	double calcMean(vector<vector<double>>);

	vector<double> tokenizeFeatures(string&);

	void increment_line(ifstream&);
};

#endif /* PREPARATION_H_ */
