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
    if (number < 7 && number > 0)
    {
        return diceStats[number];
    }
    return -1;
}

void Statistics::addDiceRoll(int diceRoll)
{
    if (diceRoll > 0 && diceRoll < 7)
    {
        numberOfTotalRolls++;
        diceStats[diceRoll]++;
    }
}

int Statistics::getNumberOfTotalRolls()
{
    return numberOfTotalRolls;
}
