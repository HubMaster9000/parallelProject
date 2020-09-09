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

double sigmoid(double x) { return 1 / (1 + exp(-x)); }
double dSigmoid(double x) { return x * (1 - x); }
double init_weight() { return ((double)rand())/((double)RAND_MAX); }
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

int main(int argc, const char * argv[]) {
     static const int numHiddenNodes = 2;

    const double lr = 0.1f;


  static const int numOutputs = 1;

    //There are 784 cols that make up each digit
    static const int numInputs = 784;
    //Training data has 60k values.
    static const int numTrainingSets = 60000;
    static const int numTestingSets = 1000;
float hiddenLayer[numHiddenNodes];
    float outputLayer[numOutputs];

    double hiddenLayerBias[numHiddenNodes];
    double outputLayerBias[numOutputs];


    float hiddenWeights[numInputs][numHiddenNodes];
    float outputWeights[numHiddenNodes][numOutputs];
  float **training_inputs = (float **)malloc(numTrainingSets * sizeof(float *));
  float **training_outputs = (float **) malloc(numTrainingSets * sizeof(float *));;
  float **testing_inputs = (float **)malloc(numTestingSets * sizeof(float *));;
  float **testing_outputs = (float **)malloc(numTestingSets * sizeof(float *));;
  struct timespec start_time_parse;
           struct timespec end_time_parse;
           clock_gettime(CLOCK_MONOTONIC,&start_time_parse);
    //Load training data
    std::ifstream trainFile("mnist_train.csv");
    // read line by line till end of trainFile
    for (int row=0; row < numTrainingSets+1; ++row) {
      //Skip first row (headers)
        if ( row != 0 ) {
            std::string trainLine;
            std::getline(trainFile, trainLine);
            if ( !trainFile.good() ) {
                break;
            }
            std::stringstream trainIss(trainLine);
            //Each row has 785 values, first is label
          training_inputs[row]= (float *)malloc(numInputs * sizeof(float));;
          training_outputs[row]=(float *) malloc(numOutputs * sizeof(float));
            for (int col = 0; col < numInputs+1; ++col) {
                std::string trainVal;
                std::getline(trainIss, trainVal, ',');
                //Converter converts string to double
            std::stringstream trainConvertor(trainVal);
            //Add first 90% of data to training
            if (col == 0) {
                //Add first col to classification
                trainConvertor >> training_outputs[row][col];
            } else {
                //Other idxs go to data
                trainConvertor >> training_inputs[row][col-1];
            }
          }
                 }
             }

             //Load testing data
             std::ifstream testingFile("mnist_test.csv");
             // read line by line till end of testing file
             for (int row=0; row < numTestingSets+1; ++row) {
                 //Skip first row (headers)
                 if ( row != 0 ) {
                   std::string testLine;
                      std::getline(testingFile, testLine);
                      if ( !testingFile.good() ) {
                          break;
                      }
                      std::stringstream testIss(testLine);
                      //Each row has 785 values, first is label
         testing_inputs[row]= (float *)malloc(numInputs * sizeof(float));;
              testing_outputs[row]= (float *)malloc(numOutputs * sizeof(float));
               for (int col = 0; col < numInputs+1; ++col) {
                          std::string testVal;
                          std::getline(testIss, testVal, ',');
               //Converter converts string to double
               std::stringstream testConvertor(testVal);
               if (col == 0) {
                   //Add first col to classification
                   testConvertor >> testing_outputs[row][col];
               } else {
                   //Other idxs go to data
                   testConvertor >> testing_inputs[row][col-1];
}
}
}
}

clock_gettime(CLOCK_MONOTONIC,&end_time_parse);
long  msec_parse = (end_time_parse.tv_sec - start_time_parse.tv_sec)*1000 + (end_time_parse.tv_nsec - start_time_parse.tv_nsec)/1000000;
printf("took to complete parse %dms\n",msec_parse);        
struct timespec start_time;
        struct timespec end_time;
        clock_gettime(CLOCK_MONOTONIC,&start_time);
  
    for (int i=0; i<numInputs; i++) {
        for (int j=0; j<numHiddenNodes; j++) {
            hiddenWeights[i][j] = init_weight();
        }
    }
    for (int i=0; i<numHiddenNodes; i++) {
        hiddenLayerBias[i] = init_weight();
        for (int j=0; j<numOutputs; j++) {
            outputWeights[i][j] = init_weight();
        }
    }
    for (int i=0; i<numOutputs; i++) {
        outputLayerBias[i] = init_weight();
    }
    
//    int trainingSetOrder[] = {0,1,2,3};
    
    for (int n=0; n < 10000; n++) {
  //      shuffle(trainingSetOrder,numTrainingSets);
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

               float  activation=outputLayerBias[j];
                for (int k=0; k<numHiddenNodes; k++) {
                    activation+=hiddenLayer[k]*outputWeights[k][j];
                }
                outputLayer[j] = sigmoid(activation);
            }
            
            std::cout << "Input:" << training_inputs[i][0] << " " << training_inputs[i][1] << "    Output:" << outputLayer[0] << "    Expected Output: " << training_outputs[i][0] << "\n";
            
           // Backprop

            
            float  deltaOutput[numOutputs];


            for (int j=0; j<numOutputs; j++) {
                double errorOutput = (training_outputs[i][j]-outputLayer[j]);
                deltaOutput[j] = errorOutput*dSigmoid(outputLayer[j]);
            }

            
            float deltaHidden[numHiddenNodes];
            for (int j=0; j<numHiddenNodes; j++) {
                double errorHidden = 0.0f;
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
    
    // Print weights
    std::cout << "Final Hidden Weights\n[ ";
    for (int j=0; j<numHiddenNodes; j++) {
        std::cout << "[ ";
        for(int k=0; k<numInputs; k++) {
            std::cout << hiddenWeights[k][j] << " ";
        }
        std::cout << "] ";
    }
    std::cout << "]\n";
    
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
    return 0;
}

