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

#include "preparation.h" // lol

using namespace std;

Preparation::Preparation() {

}

Preparation::~Preparation() {

}

vector<vector<double>> Preparation::processCSV(string fileName){
	vector<vector<double>> recordVector;
	vector<double> featureVector;
	double mean;
	ifstream csv;
	string line;

    // Open our csv file
	csv.open(fileName);
	if(!csv){
		perror("Unable to open file");
		exit(-1);
	}

	// Process lines into two dimensional array of integers
	increment_line(csv);
	string token=",";
	while(getline(csv,line)){
		featureVector=tokenizeFeatures(line);
		recordVector.push_back(featureVector);
	}
	csv.close();

	// Calculate mean of medv and replace values with 0 or 1 for above or below the mean
	mean=calcMean(recordVector);
	recordVector=replaceMedv(recordVector,mean);

	return recordVector;
}

vector<vector<double>> Preparation::separateTrain(vector<vector<double>> fullSet){
	vector<vector<double>>trainingVec;
	int training_size=fullSet.size()*0.9;
	for(int i=0;i<training_size;i++) {
		trainingVec.push_back(fullSet[i]);
	}
	return trainingVec;
}

vector<vector<double>> Preparation::separateTest(vector<vector<double>> fullSet){
	vector<vector<double>>testingVec;
	int testing_start=fullSet.size()*0.9;
	int testing_stop=fullSet.size();
	for(int i=testing_start;i<testing_stop;i++) {
		testingVec.push_back(fullSet[i]);
	}
	return testingVec;

}

vector<double> Preparation::gatherMedVs(vector<vector<double>> vec){
	vector<double> medVs;
	int size=vec.size();
	for(int i=0;i<size;i++) medVs.push_back(vec[i][MEDV_LOC]);
	return medVs;
}

vector<vector<double>> Preparation::dropMedVs(vector<vector<double>> vec){
	vector<vector<double>> new_vec=vec;
	int size=vec.size();
	for(int i=0;i<size;i++) new_vec[i].pop_back();
	return new_vec;
}

long Preparation::getRandomLong(){
	long random=0;
	int fd=0;
	if((fd=open("/dev/urandom",O_RDONLY))==0){
		perror("Unable to open /dev/urandom for seeding rng");
		exit(-1);
	}
	if(read(fd,&random,sizeof(long))<=0){
		perror("Unable to read /dev/urandom for seeding rng");
		exit(-1);
	}
	close(fd);
	return random;
}

vector<vector<double>> Preparation::replaceMedv(vector<vector<double>> vec,double mean){
	vector<vector<double>> newVec=vec;
	int vec_size=vec.size();

	for(int i=0;i<vec_size;i++){
		if(vec[i][MEDV_LOC]<=mean) newVec[i][MEDV_LOC]=0;
		else newVec[i][MEDV_LOC]=1;
	}
	return newVec;
}

double Preparation::calcMean(vector<vector<double>> vec){
	double mean=0;
	int vector_size=vec.size();

	// medv is the MEDV_LOCth element
	for(int i=0;i<vector_size;i++){
		mean+=vec[i][MEDV_LOC];
	}
	mean=mean/(double)vector_size;
	return mean;
}

vector<double> Preparation::tokenizeFeatures(string& str){
	vector<double> feats;
	vector<std::string> words;
	string s;
	boost::split(words, str, boost::is_any_of(","), boost::token_compress_on);
	for(int i=0;i<(signed int)words.size();i++){
		boost::erase_all(words[i],"\"");
		feats.push_back(stod(words[i]));
	}
	return feats;
}

void Preparation::increment_line(ifstream& file){
	string line;
	getline(file,line);
	return;
}
