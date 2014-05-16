// Ben Poland
// Random Number Generator Class

// Note: Problem, this class as it stands now cannot gnerate more than one instance
//			if another instance is called it will reseed both instances

#ifndef _RANDOM_H
#define _RANDOM_H

#include <cstdlib>
#include <ctime>

class Random
{
private:
	// Random number properties
	time_t time_seed;
	time_t seed;
		
public:
	// Constructors
	Random();				// Seeds with the system clock
	Random(int i);			// Seeds using the given value

	// Destructor
	~Random();

	// Accessor funciton
	time_t getSeed()	{return seed;}

	// Member function
	int rNum();				// Generates a random number
};

#endif