/*
 * randomt.h
 *
 *  Created on: Nov 20, 2012
 *      Author: chjd
 */

#ifndef RANDOMT_H_
#define RANDOMT_H_

/*
 * usage of random function

// ref: http://en.cppreference.com/w/cpp/numeric/random

#include <cstdlib>
#include <ctime>
#include <random>

//use current time as seed for random generator
std::srand(std::time(0));

// return pesudo-random number between [0,RAND_MAX]
int rand();

// uniform distribution
std::random_device rd;
std::mt19937 gen(rd());
or
std::default_random_engine gen(rd());
std::uniform_real_distribution<> dis(1, 2);

dis(gen);

 */



#endif /* RANDOMT_H_ */
