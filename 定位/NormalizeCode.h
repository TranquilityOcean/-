//=================================================================================
// Name        : help_functions.h
// Version     : 2.0.0
// Copyright   : Udacity
//=================================================================================

#ifndef NORMALIZE_FUNCTIONS_H_
#define NORMALIZE_FUNCTIONS_H_

#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

class Normalize {
public:

	//static function to normalize a vector:
	static std::vector<float> normalize_vector(std::vector<float> inputVector){

		//declare sum:
		float sum = 0.0f;

		//declare and resize output vector:
		std::vector<float> outputVector ;
		outputVector.resize(inputVector.size());

		//estimate the sum:
		for (unsigned int i = 0; i < inputVector.size(); ++i) {
			sum += inputVector[i];
		}

		//normalize with sum:
		for (unsigned int i = 0; i < inputVector.size(); ++i) {
			outputVector[i] = inputVector[i]/sum;
		}

		//return normalized vector:
		return outputVector;
	}
	
};

#endif /* NORMALIZE_FUNCTIONS_H_ */