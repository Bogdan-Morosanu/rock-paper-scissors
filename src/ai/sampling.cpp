#include "sampling.hpp"

namespace ai
{
    rps::Move sample(const std::array<double, 3> &distribution)
    {
	const int resolution = 100;

	const double r = double(std::rand() % resolution);
	const double cut1 = resolution * distribution[0];
	const double cut2 = cut1 + resolution * distribution[1];
	
	if (r < cut1) {
	    return rps::Move::ROCK;
	    
	} else if (r < cut2) {
	    return rps::Move::PAPER;

	} else {
	    return rps::Move::SCISSORS;
	}
    }
}

