#include <iostream>
#include <algorithm>
#include <vector>

#include "gaussianCode.h"
using namespace std;

//initialize priors assumimg vehicle at landmark +/- 1.0 meters position stdev
std::vector<float> initialize_priors(int map_size, std::vector<float> landmark_positions,
                                     float position_stdev);
									 
float motion_model(float pseudo_position, float movement, std::vector<float> priors,
                   int map_size, int control_stdev);
int main() {
    //set standard deviation of control:
    float control_stdev = 1.0f;
	
    //set standard deviation of position:
    float position_stdev = 1.0f;

    //meters vehicle moves per time step
    float movement_per_timestep = 1.0f;
	
    //set map horizon distance in meters 
    int map_size = 25;

    //initialize landmarks
    std::vector<float> landmark_positions {5, 10, 20};

    // initialize priors
    std::vector<float> priors = initialize_priors(map_size, landmark_positions,
                                                  position_stdev);
    //step through each pseudo position x(i)
	for (unsigned int i = 0;i< map_size;++i){
		float pseudo_position = float(i);
		
		//get the motion model probability for each x position
		float motion_prob = motion_model(pseudo_position, movement_per_timestep,
                            priors, map_size, control_stdev);
		//print to stdout
		std::cout << pseudo_position << "\t" <<motion_prob <<endl;
	}
    //print values to stdout 
/*     for (unsigned int p = 0; p < priors.size(); p++) {
        std::cout << priors[p] << endl;
    } */     
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
//TODO, implement the motion model: calculates prob of being at an estimated position at time t 
float motion_model(float pseudo_position, float movement, std::vector<float> priors,
			   int map_size, int control_stdev)
{
	//initialize probability
	float position_prob = 0.0f;
	//Your Code Here
	//loop over state space for all possible position x(convolution):
	for(unsigned int j = 0;j < map_size;++j){
		float next_pseudo_position = float(j);
		//distance from i to j
		float distance_ij = pseudo_position - next_pseudo_position;
		//transition probabilities:
		float transition_prob = gaussianCode::normpdf(distance_ij,movement,control_stdev);
		//estimate probability for the motion model,this is our prior 
		position_prob += transition_prob * priors[j];
	}
	return position_prob;
}




















