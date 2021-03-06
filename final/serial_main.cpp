//
//  main.cpp
//  NeuralNetwork
//
//  Created by Santiago Becerra on 9/15/19.
//  Copyright © 2019 Santiago Becerra. All rights reserved.
//
//

#include <iostream>
#include <list>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <iostream>


// Simple network that can learn XOR
// Feartures : sigmoid activation function, stochastic gradient descent, and mean square error fuction

// Potential improvements :
// Different activation functions
// Batch training
// Different error funnctions
// Arbitrary number of hidden layers
// Read training end test data from a file
// Add visualization of training

float sigmoid(float x) { return 1 / (1 + exp(-x)); }
float dSigmoid(float x) { return x * (1 - x); }
float init_weight() { return ((float)rand())/((float)RAND_MAX); }
void shuffle(int *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

//Assign label for testing accuracy
float assignLabel( int i, float *testing_input, int numHiddenNodes, int numInputs, float **hiddenWeights, float *hiddenLayer, int numOutputs, float **outputWeights, float *outputLayer) {
    float label = 0;
    //Return 1 if x >=0 else return 0
    for (int j=0; j<numHiddenNodes; j++) {

        float activation = 0;
            for (int k=0; k<numInputs; k++) {
            activation += testing_input[k]*hiddenWeights[k][j];;
        }
        hiddenLayer[j] = sigmoid(activation);
    }
    
    for (int j=0; j<numOutputs; j++) {

        float activation = 0;
        for (int k=0; k<numHiddenNodes; k++) {
            activation += hiddenLayer[k]*outputWeights[k][j];
        }
        label = sigmoid(activation);
    }
    
    if ( label > 0 ) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, const char* argv[]) {
    static const int numHiddenNodes = 2;
std::istringstream ss(argv[1]);

int it; 
ss>>it; 
    const float lr = 0.1f;


    static const int numOutputs = 1;

    //There are 784 cols that make up each digit
    static const int numInputs = 785;
    //Training data has 60k values.
    static const int numTrainingSets = 60000;
    static const int numTestingSets = 10000;
    float hiddenLayer[numHiddenNodes];
    float outputLayer[numOutputs];

    float hiddenLayerBias[numHiddenNodes];
    float outputLayerBias[numOutputs];


    float **hiddenWeights = (float **)malloc(numInputs * sizeof(float *));
    float **outputWeights = (float **)malloc(numHiddenNodes * sizeof(float *));  
    float **training_inputs = (float **)malloc(numTrainingSets * sizeof(float *));
    float **training_outputs = (float **) malloc(numTrainingSets * sizeof(float *));;
    float **testing_inputs = (float **)malloc(numTestingSets * sizeof(float *));;
    float **testing_outputs = (float **)malloc(numTestingSets * sizeof(float *));;
    struct timespec end_time;
    struct timespec start_time;
    struct timespec end_time_parse;
    clock_gettime(CLOCK_MONOTONIC,&start_time);

    std::string train;
    std::ifstream trainFile("mnist_train.csv");
    std::getline(trainFile, train);


    std::string test;
    std::ifstream testingFile("mnist_test.csv");
    std::getline(testingFile, test);
    
    //Load training data
    // read line by line till end of trainFile
    for (int row=0; row < numTrainingSets; ++row) {
        std::string trainLine;
        std::getline(trainFile, trainLine);
        std::stringstream trainIss(trainLine);
        //Each row has 785 values, first is label
        training_inputs[row]= (float *)malloc(numInputs * sizeof(float));;
        training_outputs[row]=(float *) malloc(numOutputs * sizeof(float));
        for (int col = 0; col < numInputs; ++col) {
            std::string trainVal;
            std::getline(trainIss, trainVal, ',');
            //Converter converts string to float
            std::stringstream trainConvertor(trainVal);
            if (col == 0) {
                //Add first col to classification
                trainConvertor >> training_outputs[row][col];
            } else {
                //Other idxs go to data
                trainConvertor >> training_inputs[row][col-1];
            }
        }
}
    //Load testing data
    // read line by line till end of testing file
    for (int row=0; row < numTestingSets; ++row) {
        std::string testLine;
        std::getline(testingFile, testLine);

        std::stringstream testIss(testLine);
        //Each row has 785 values, first is label
        testing_inputs[row]= (float *)malloc(numInputs * sizeof(float));;
        testing_outputs[row]= (float *)malloc(numOutputs * sizeof(float));
        for (int col = 0; col < numInputs; ++col) {
            std::string testVal;
            std::getline(testIss, testVal, ',');
            //Converter converts string to float
            std::stringstream testConvertor(testVal);
            if (col == 0) {
                //Add first col to classification
                testConvertor >> testing_outputs[row][col];
            } else {
                //Other idxs go to data
                testConvertor >> testing_inputs[row][col-1];
            }
        }}

    clock_gettime(CLOCK_MONOTONIC,&end_time_parse);
    long  msec_parse = (end_time_parse.tv_sec - start_time.tv_sec)*1000 + (end_time_parse.tv_nsec - start_time.tv_nsec)/1000000;

    printf("took to complete parse %dms\n",msec_parse);        
  
    for (int i=0; i<numInputs; i++) {
        hiddenWeights[i]=(float *) malloc(numHiddenNodes * sizeof(float));

        for (int j=0; j<numHiddenNodes; j++) {
            hiddenWeights[i][j] = init_weight();
        }
    }
    for (int i=0; i<numHiddenNodes; i++) {
        outputWeights[i]=(float *) malloc(numOutputs * sizeof(float));
        hiddenLayerBias[i] = init_weight();
        for (int j=0; j<numOutputs; j++) {
            outputWeights[i][j] = init_weight();
        }
    }
    for (int i=0; i<numOutputs; i++) {
        outputLayerBias[i] = init_weight();
    }
    
for (int n=0; n < it; n++) {
        for (int x=0; x<numTrainingSets; x++) {
            
            int i = x;
            // Forward pass

            for (int j=0; j<numHiddenNodes; j++) {

               float activation=hiddenLayerBias[j];
                 for (int k=0; k<numInputs; k++) {
                    activation+=training_inputs[i][k]*hiddenWeights[k][j];
                }
                hiddenLayer[j] = sigmoid(activation);
            }

            for (int j=0; j<numOutputs; j++) {

               float activation=outputLayerBias[j];
                for (int k=0; k<numHiddenNodes; k++) {
                    activation+=hiddenLayer[k]*outputWeights[k][j];
                }
                outputLayer[j] = sigmoid(activation);
            }
            float  deltaOutput[numOutputs];


            for (int j=0; j<numOutputs; j++) {
                float errorOutput = (training_outputs[i][j]-outputLayer[j]);
                deltaOutput[j] = errorOutput*dSigmoid(outputLayer[j]);
            }


            float deltaHidden[numHiddenNodes];
            for (int j=0; j<numHiddenNodes; j++) {
                float errorHidden = 0.0f;
                for(int k=0; k<numOutputs; k++) {
                    errorHidden+=deltaOutput[k]*outputWeights[j][k];
                }
                deltaHidden[j] = errorHidden*dSigmoid(hiddenLayer[j]);
            }

            for (int j=0; j<numOutputs; j++) {
                outputLayerBias[j] += deltaOutput[j]*lr;
                for (int k=0; k<numHiddenNodes; k++) {
                    outputWeights[k][j]+=hiddenLayer[k]*deltaOutput[j]*lr;
                }
            }

            for (int j=0; j<numHiddenNodes; j++) {
                hiddenLayerBias[j] += deltaHidden[j]*lr;
                for(int k=0; k<numInputs; k++) {
                    hiddenWeights[k][j]+=training_inputs[i][k]*deltaHidden[j]*lr;
                }
            }
        }
    }
    
    std::cout << "Final Hidden Biases\n[ ";
    for (int j=0; j<numHiddenNodes; j++) {
        std::cout << hiddenLayerBias[j] << " ";

    }
    std::cout << "]\n";
    std::cout << "Final Output Weights";
    for (int j=0; j<numOutputs; j++) {
        std::cout << "[ ";
        for (int k=0; k<numHiddenNodes; k++) {
            std::cout << outputWeights[k][j] << " ";
        }
        std::cout << "]\n";
    }
    std::cout << "Final Output Biases\n[ ";
    for (int j=0; j<numOutputs; j++) {
        std::cout << outputLayerBias[j] << " ";

    }
    std::cout << "]\n";
    struct timespec start_test; 
    clock_gettime(CLOCK_MONOTONIC,&start_test);

    //Test model for accuracy
    int correctPredictions = 0;
    //loop through test data and see if predicted label matches actual label
    for ( int i = 0; i < numTestingSets; i++ ) {
        float predictedLabel = assignLabel( i, testing_inputs[i], numHiddenNodes, numInputs, hiddenWeights, hiddenLayer, numOutputs, outputWeights, outputLayer );
        if ( predictedLabel == testing_outputs[i][0] ) {
            correctPredictions++;
        }
    }
    float correctPercentage = (correctPredictions / double(numTestingSets)) * 100;
    printf("Correct Prediction Percentage %.2f% \n", correctPercentage);


    clock_gettime(CLOCK_MONOTONIC,&end_time);
  long msec_test = (end_time.tv_sec - start_test.tv_sec)*1000 + (end_time.tv_nsec - start_test.tv_nsec)/1000000;
    printf("took to complete test %dms\n", msec_test);
    long msec_total = (end_time.tv_sec - start_time.tv_sec)*1000 + (end_time.tv_nsec - start_time.tv_nsec)/1000000;
    printf("took to complete whole program %dms\n", msec_total);
return 0; 
}
