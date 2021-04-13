// BullsAndCows_letters.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// "Bulls and Cows" game, for rules, see definition of bullsAndCows() in this file
//
//

// In ASCII table letters from A to Z have a 65-90 dec. range

#include "randomize.h"

#include <iostream>
#include <vector>
#include <ctime>


void printWelcome()
{
    std::cout << "\tBULLS AND COWS\n\n"
        << "Computer drawn 4 capital letters (letters are different from each other).\n"
        << "Try to guess them!\n\n";

    std::cout << "These are some hints for you:\n"
        << "If a letter in a guess is on the right position in the letters drawn\n"
        << "it's considered as a \"bull\".\n"
        << "If a letter in a guess is in the letters drawn, but not on the right position\n"
        << "it's considered as a \"cow\".\n\n\n\n";
}

bool isRepeated(std::vector<char> guess, char letter)
{
    for (char lett : guess)
    {
        if (lett == letter)
        {
            return true;
        }
    }

    return false;
}

// reads 4 different digits from console
// prompts user to make a correct input
void enterGuess(std::vector<char>& guess)
{
    bool isFail{ true };

    while (isFail)
    {
        isFail = false;
        guess.clear();

        char temp{};
        // pushes 4 letters from console to the guess vector
        for (int i = 0; i < 4; ++i)
        {
            std::cin.get(temp);

            // prevents input which is too short or has non-digit characters
            if (temp < 65 || temp > 90)
            {
                isFail = true;
                std::cin.putback(temp);
                std::cout << "Wrong input, try again: ";
                break;
            }

            char letter{ temp };

            // prevents repeated digits in a guess
            if (isRepeated(guess, letter))
            {
                isFail = true;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.putback('\n');
                std::cout << "Wrong input, try again: ";
                break;
            }

            guess.push_back(letter);
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

void printScore(int bulls, int cows, int counter)
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
        std::cout << "You had " << counter << " guesses.\n\n";
    }
        
}

// User try to guess randomly drawn 4 capital letters (letters are different from each other).
// If a letter in a guess is on the right position in the letters drawn, it's considered as a "bull".
// If a letter in a guess is in the letters drawn, but not on the right position, it's considered as a "cow".
//
// User is notified about the number of bulls and cows in his guess
// and plays until there are 4 bulls in a guess (the guess is correct).
void bullsAndCows()
{
    std::vector<char> toGuessVec;

    randomizeLetters(toGuessVec, 4); // see randomize.h or randomize.cpp
    if (toGuessVec.size() != 4)
        throw std::runtime_error("bullsAndCows(): randomizeDigits_two(std::vector<int> v, int n) shoud have n = 4");

    printWelcome();

    short bulls{ 0 };
    short cows{ 0 };

    std::vector<char> guess;
    int guessCount{ 0 };

    while (bulls != 4)
    {
        ++guessCount;
        bulls = 0;
        cows = 0;

        // For debugging
        /*
        std::cout << "Aswer: ";
        for (char letter : toGuessVec)
            std::cout << letter;
        */

        std::cout << "Enter 4 different letters (e.g. ABCD): ";
        enterGuess(guess);

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (guess[i] == toGuessVec[j])
                {
                    if (i == j)
                        ++bulls;
                    else
                        ++cows;
                }
            }
        }

        printScore(bulls, cows, guessCount);
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