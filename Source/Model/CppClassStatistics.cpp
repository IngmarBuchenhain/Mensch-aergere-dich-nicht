#include "CppClassStatistics.hpp"
#include <iostream>

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

void Statistics::showDiceStats()
{
    std::cout << std::endl
              << "Dice statistics" << std::endl;
    std::cout << "Number of total dice rolls: " << numberOfTotalRolls << std::endl;
    std::cout << "Dice distribution:" << std::endl;
    for (int diceNumber = 1; diceNumber < 7; diceNumber++)
    {

        std::cout << diceNumber << ": ";
        if (diceStats[diceNumber] < 100 && diceStats[diceNumber] > 9)
        {
            std::cout << " ";
        }
        else if (diceStats[diceNumber] < 10)
        {
            std::cout << "  ";
        }
        std::cout << diceStats[diceNumber] << " ";
        double normalizedNumber = ((double)diceStats[diceNumber] / (double)numberOfTotalRolls) * 400;
        int temp = (int)normalizedNumber;
        for (int index = 0; index < temp; index++)
        {
            std::cout << "\u25A0"; //\u25A0\u25A0\u25A0\u25A0";//<< "|||||";
        }
        std::cout << std::endl;
    }
}