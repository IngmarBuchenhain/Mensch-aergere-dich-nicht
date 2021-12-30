#include "CppClassDice.hpp"

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