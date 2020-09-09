#define _OPEN_SYS_ITOA_EXT
#include <omp.h>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// Preprocesser for MNIST digit data

int main() {
    //First col has an int to label the number
    static const int numOutputs = 1;
    //There are 784 cols that make up each digit
    static const int numInputs = 784;
    //Training data has 60k values.
    static const int numTrainingSets = 60000;
    //Testing data has 10k values.
    static const int numTestingSets = 10000;
    double training_inputs[numTrainingSets][numInputs];
    double training_outputs[numTrainingSets][numOutputs];
    double testing_inputs[numTestingSets][numInputs];
    double testing_outputs[numTestingSets][numOutputs];

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

    return 0;
}