#ifndef RANDOMIZE_H
#define RANDOMIZE_H

#include <vector>

// makes vec a n-letter vector, with each letter being different from each other
// n must be from 1 to 10 - throws runtime_error otherwise
void randomizeLetters(std::vector<char>& vec, int n);

#endif