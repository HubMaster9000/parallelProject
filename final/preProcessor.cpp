#define _OPEN_SYS_ITOA_EXT
#include <omp.h>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// Preprocesser for breast cancer data

int main() {
    static const int numInputs = 30;
    static const int numOutputs = 1;
    static const int numTrainingSets = 512;
    static const int numTestingSets = 57;
    float training_inputs[numTrainingSets][numInputs];
    float training_outputs[numTrainingSets][numOutputs];
    float testing_inputs[numTestingSets][numInputs];
    float testing_outputs[numTestingSets][numOutputs];
    
    std::ifstream file("breast-cancer-data.csv");
    // read line by line till end of file
    for (int row=0; row < 569; ++row) {
        std::string line;
        std::getline(file, line);
        if ( !file.good() ) {
            break;
        }
        std::stringstream iss(line);

        for (int col = 0; col < 31; ++col) {
            std::string val;
            std::getline(iss, val, ',');


            std::stringstream convertor(val);
            //Add first 90% of data to training
            if (row < 512) {
                if (col == 0) {
                    //Add first col to classification
                    convertor >> training_outputs[row][col];
                } else {
                    //Other idxs go to data
                    convertor >> training_inputs[row][col-1];
                }
            } else {
                //Add last 10% to testing data
                if (col == 0) {
                    //Add first col to classification
                    convertor >> testing_outputs[row][col];
                } else {
                    //Other idxs go to data
                    convertor >> testing_inputs[row][col-1];
                }
            }
        }
    }
    return 0;
}