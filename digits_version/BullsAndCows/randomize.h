#ifndef RANDOMIZE_H
#define RANDOMIZE_H

#include <vector>

// makes vec a n-digit vector, with each digit being different from each other
// n must be from 1 to 10 - throws runtime_error otherwise
void randomizeDigits_one(std::vector<int>& vec, int n);

// makes vec a n-digit vector, with each digit being different from each other
// n must be from 1 to 10 - throws runtime_error otherwise
void randomizeDigits_two(std::vector<int>& vec, int n);

#endif