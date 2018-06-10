# Perceptron
An implementation of the Perceptron Learning Algorithm in C++

Program is designed to predict low/high of median housing price
based on Boston housing dataset in 'boston.csv'.

The number of training epochs is passed in through command line
argument at runtime.

Expected usage is \<program\> \<options\> \<number of epochs\>

Available options are: --shuffle (default) and --no-shuffle to specify whether to shuffle records before each epoch

Requires boost library for Preparation Object
Boost can be installed on Debian/Ubuntu systems with apt-get install libboost-dev

Written by Jonathan Pennington
