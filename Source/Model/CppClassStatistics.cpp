#include "CppClassStatistics.hpp"

Statistics::Statistics()
{
    numberOfTotalRolls = 0;
    for (int diceNumber = 0; diceNumber < 7; diceNumber++)
    {
        diceStats[diceNumber] = 0;
    }
}

int Statistics::getNumberRolls(int number)
{
    return diceStats[number];
}

void Statistics::addDiceRoll(int diceRoll)
{
    numberOfTotalRolls++;
    diceStats[diceRoll]++;
}

int Statistics::getNumberOfTotalRolls()
{
    return numberOfTotalRolls;
}
