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
#include "perceptron.h"

int main(int argc, char ** argv){

    // Variables
    string fileName=FILENAME;
    vector<vector<double>> processedVector;
    vector<double> weights;
    vector<vector<double>> trainingVector;
    vector<vector<double>> testingVector;
    vector<vector<double>> trainingNoMedv;
    vector<double> medvs;
    int testing_size;
    int num_feats;
    int epochs;
    int prediction;
    int right;
    int wrong;

    // Check for epochs on the command line
    if(argc!=2){
        cout<<"Usage: <program> <number of epochs>\n";
        exit(-1);
    }

    if((epochs=atoi(argv[1]))==0){
        cout<<"Please choose an epoch size greater than zero\n";
        exit(-1);
    }

    // Let them know what we're doing
    cout<<"Running Perceptron with "<< epochs << " epochs\n";

    // Create the objects Preppy the Preparation and Percy the Perceptron
    Preparation Preppy;
    Perceptron Percy;

    // Setup RNG
    auto randy = default_random_engine {};
    randy.seed((unsigned long) Preppy.getRandomLong());

    // Normal distribution appears to work better than uniform
    normal_distribution<double> dist(-1,1);

    // Get a processed vector of our data
    processedVector=Preppy.processCSV(fileName);

    // Separate training and testing data (90% training, 10% testing)
    trainingVector=Preppy.separateTrain(processedVector);
    testingVector=Preppy.separateTest(processedVector);

    // Initialize weights
    num_feats=(int)processedVector[0].size()-1;
    for(int i=0;i<num_feats;i++){
        weights.push_back(dist(randy));
    }

    for(int i=0;i<epochs;i++){

        // Shuffle Vector everytime we train
        shuffle(begin(trainingVector), end(trainingVector), randy);

        // Separate mean from training data
        medvs=Preppy.gatherMedVs(trainingVector);
        trainingNoMedv=Preppy.dropMedVs(trainingVector);

        // Train, updating weights
        weights=Percy.train(trainingNoMedv,medvs,weights);

    }

    testing_size=testingVector.size();
    prediction=0;
    right=0;
    wrong=0;

    // Gather the new medVs for testing how we've learned
    medvs=Preppy.gatherMedVs(testingVector);

    // Test how much we've learned
    for(int i=0;i<testing_size;i++){
        prediction=Percy.predict(testingVector[i],weights);
        if(prediction==medvs[i]){
            right++;
        }
        else wrong++;
    }
    cout<<"We were right "<<((double)right/(double)((double)right+(double)wrong)*(double)100) <<"% of the time\n";
    return 0;
}
