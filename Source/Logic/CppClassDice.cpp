#include "CppClassDice.hpp"
#include<random>

// Will be used to obtain a seed for the random number engine.
std::random_device rd;

// Standard mersenne_twister_engine seeded with rd().
std::mt19937 gen(rd());

/**
 * Returns random number based on std::mt19937 and std:random_device.
 */
int getRandomNumberBetween(int lower, int upper)
{
    std::uniform_int_distribution<> dis(lower, upper);
    return dis(gen);
}

/**
* Default constructor.
*/
Dice::Dice() {}

/**
* Roll the dice and return a number between 1 and 6 (including).
*/
int Dice::roll()
{
    return getRandomNumberBetween(1, 6);
}
int Dice::getStartPlayer(int numberOfPlayers){
    return getRandomNumberBetween(0, numberOfPlayers - 1);
}