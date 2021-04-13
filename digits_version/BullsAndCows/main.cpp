// "Bulls and Cows" game, for rules, see definition of bullsAndCows() in this file
//
//

#include "randomize.h"

#include <iostream>
#include <vector>
#include <ctime>

void printWelcome()
{
    std::cout << "\tBULLS AND COWS\n\n"
        << "Computer drawn 4 digit number (digits are different from each other).\n"
        << "Try to guess it!\n\n";

    std::cout << "These are some hints for you:\n"
        << "If a digit in a guess is on the right position in the number drawn\n"
        << "it's considered as a \"bull\".\n"
        << "If a digit in a guess is in the number drawn, but not on the right position\n"
        << "it's considered as a \"cow\".\n\n\n\n";
}

bool isRepeated(std::vector<int> guess, int digit)
{
    for (int dig : guess)
    {
        if (dig == digit)
        {
            return true;
        }
    }
    
    return false;
}

// reads 4 different digits from console
// prompts user to make a correct input
void enterGuess(std::vector<int>& guess)
{
    bool isFail{ true };

    while (isFail)
    {
        isFail = false;
        guess.clear();

        char temp{};
        // pushes 4 digits from console to the guess vector
        for (int i = 0; i < 4; ++i)
        {
            std::cin.get(temp);

            // prevents input which is too short or has non-digit characters
            if (temp < 48 || temp > 57)
            {
                isFail = true;
                std::cin.putback(temp);
                std::cout << "Wrong input, try again: ";
                break;
            }

            int digit{ static_cast<int>(temp) - 48 };

            // prevents repeated digits in a guess
            if (isRepeated(guess, digit))
            {
                isFail = true;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.putback('\n');
                std::cout << "Wrong input, try again: ";
                break;
            }

            guess.push_back(digit);
        }

        // prevents input which is too long
        if (std::cin.peek() != '\n')
        {
            isFail = true;
            std::cout << "Wrong input, try again: ";
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.clear();
    }
}

void printScore(int bulls, int cows, int tryCount)
{
    std::cout << bulls << ' ';
    if (bulls == 1)
        std::cout << "bull";
    else
        std::cout << "bulls";

    std::cout << " and " << cows << ' ';
    if (cows == 1)
        std::cout << "cow";
    else
        std::cout << "cows";

    std::cout << "!\n";

    if (bulls == 4)
    {
        std::cout << "YOU WIN!!!\n";
        std::cout << "You have tried " << tryCount << " times.\n\n";
    }
}

// User try to guess a random 4 digit number (digits are different from each other).
// If a digit in a guess is on the right position in the number drawn, it's considered as a "bull".
// If a digit in a guess is in the number drawn, but not on the right position, it's considered as a "cow".
//
// User is notified about the number of bulls and cows in his guess
// and plays until there are 4 bulls in a guess (the guess is correct).
void bullsAndCows()
{
    std::vector<int> numToGuess;

    randomizeDigits_two(numToGuess, 4); // see randomize.h or randomize.cpp
    if (numToGuess.size() != 4)
        throw std::runtime_error("bullsAndCows(): randomizeDigits_two(std::vector<int> v, int n) shoud have n = 4");

    printWelcome();

    short bulls{ 0 };
    short cows{ 0 };
    int tryCount{ 0 };

    std::vector<int> guess;

    while (bulls != 4)
    {
        bulls = 0;
        cows = 0;

        // For debugging
        /*
        std::cout << "Aswer: ";
        for (int dig : numToGuess)
            std::cout << dig;
        */

        std::cout << "Enter 4 different digits (e.g. 1234): ";
        enterGuess(guess);
        ++tryCount;

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (guess[i] == numToGuess[j])
                {
                    if (i == j)
                        ++bulls;
                    else
                        ++cows;
                }
            }
        }

        printScore(bulls, cows, tryCount);
    }
}

bool retry() 
{
    std::cout << "Do you want to try again? (y/n): ";

    while (true)
    {
        char answ{};
        std::cin >> answ;

        if (answ == 'y')
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.clear();
            return 1;
        }
            
        else if (answ == 'n')
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.clear();
            return 0;
        }
           
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.clear();
    }
}

int main()
{
    srand(time(NULL));

    do
    {
        try {
            bullsAndCows();
        }
        catch (std::runtime_error e) {
            std::cout << "Error: " << e.what() << '\n';
        }
    } while (retry());

    return 0;
}