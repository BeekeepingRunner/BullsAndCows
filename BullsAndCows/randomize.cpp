// Two versions of a function that makes a vector which store n different digits, where 1 <= n <= 10.
// In another words, these functions create a k-permutation of 9, where 1 <= k <= 10.

#include "randomize.h"

#include <vector>
#include <stdexcept>

// makes vec a n-digit vector, with each digit being different from each other
// n must be from 1 to 10 - throws runtime_error otherwise
void randomizeDigits_one(std::vector<int>& vec, int n)
{
    if (n < 1 || n > 10)
        throw std::runtime_error("randomizeDigits(): n in a bad range");

    vec.clear();
    vec.push_back(rand() % 10);

    for (int i = 1; i < n; ++i)
    {
        int draw{ 0 };
        bool isRepeated{ true };

        while (isRepeated)
        {
            isRepeated = false;
            draw = rand() % 10;

            for (int digit : vec)
            {
                if (digit == draw)
                    isRepeated = true;
            }
        }

        vec.push_back(draw);
    }
}

// makes vec a n-digit vector, with each digit being different from each other
// n must be from 1 to 10 - throws runtime_error otherwise
void randomizeDigits_two(std::vector<int>& vec, int n)
{
    if (n < 1 || n > 10)
        throw std::runtime_error("randomizeDigits(): n in a bad range");

    // we use bool[9] array to indicate which numbers (from 0 to 9) are available (true) to draw
    std::vector<bool> toDraw{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    int draw{ rand() % 10 };

    for (int i = 0; i < n; ++i)
    {
        while (!toDraw[draw])
        {
            draw = rand() % 10;
        }

        toDraw[draw] = false;
        vec.push_back(draw);
    }
}