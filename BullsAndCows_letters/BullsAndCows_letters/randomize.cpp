// Two versions of a function that makes a vector which store n different digits, where 1 <= n <= 10.
// In another words, these functions create a k-permutation of 9, where 1 <= k <= 10.

#include "randomize.h"

#include <vector>
#include <stdexcept>

// makes vec a n-letter vector, with each letter being different from each other
// n must be from 1 to 10 - throws runtime_error otherwise
void randomizeLetters(std::vector<char>& vec, int n)
{
    if (n < 1 || n > 10)
        throw std::runtime_error("randomizeDigits(): n in a bad range");

    vec.clear();
    vec.push_back(static_cast<char>(rand() % 25 + 65));

    for (int i = 1; i < n; ++i)
    {
        int draw{ 0 };
        bool isRepeated{ true };

        while (isRepeated)
        {
            isRepeated = false;
            draw = static_cast<char>(rand() % 25 + 65);

            for (int letter : vec)
            {
                if (letter == draw)
                    isRepeated = true;
            }
        }

        vec.push_back(draw);
    }
}