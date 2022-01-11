#ifndef MAEDN_CLASS_STATISTICS_HPP
#define MAEDN_CLASS_STATISTICS_HPP

#include <vector>

/**
 * Simple class to provide some statistics to the game
 */
class Statistics
{
    int numberOfTotalRolls;

    int diceStats[7]; // 7 so we can access each number directly

public:
    /**
     * Init and reset to 0.
     */
    Statistics();

public:
    /**
     * Add to statistics the number which was rolled.
     */
    void addDiceRoll(int diceRoll);

public:
    /**
     * Get number of total rolls.
     */
    int getNumberOfTotalRolls();

public:
    /**
     * Get the count how many times a number was rolled.
     */
    int getNumberRolls(int number);
};

#endif