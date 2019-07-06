#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//initialize priors assumimg vehicle at landmark +/- 1.0 meters position stdev
std::vector<float> initialize_priors(int map_size, std::vector<float> landmark_positions,
                                     float position_stdev);

int main() {

    //set standard deviation of position:
    float position_stdev = 1.0f;

    //set map horizon distance in meters 
    int map_size = 25;

    //initialize landmarks
    std::vector<float> landmark_positions {5, 10, 20};

    // initialize priors
    std::vector<float> priors = initialize_priors(map_size, landmark_positions,
                                                  position_stdev);
    
    //print values to stdout 
    for (unsigned int p = 0; p < priors.size(); p++) {
        std::cout << priors[p] << endl;
    }
        
    return 0;

};

//TODO: Complete the initialize_priors function
std::vector<float> initialize_priors(int map_size, std::vector<float> landmark_positions,
                                     float position_stdev) {

//initialize priors assumimg vehicle at landmark +/- 1.0 meters position stdev

    //set all priors to 0.0
    std::vector<float> priors(map_size, 0.0);
    
    //YOUR CODE HERE
	//求出标准差影响的总位置数
	float normalization_term = landmark_positions.size() * (position_stdev * 2 + 1);
	for (unsigned int i = 0; i < landmark_positions.size(); i++){
        int landmark_center = landmark_positions[i]-1;
		priors[landmark_center] = 1.0f/normalization_term;
		for(int j = 1;j <= position_stdev;j++){
			priors[landmark_center - j] = 1.0f/normalization_term;
			priors[landmark_center + j] = 1.0f/normalization_term;
		}
        

    }
    return priors;
}