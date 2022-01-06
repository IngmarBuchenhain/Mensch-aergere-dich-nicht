#ifndef MAEDN_CLASS_STATISTICS_HPP
#define MAEDN_CLASS_STATISTICS_HPP

#include<vector>

class Statistics{
    int numberOfTotalRolls;
    //std::vector<int> diceStats;
    int diceStats[7];

    public:
    Statistics();
    void addDiceRoll(int diceRoll);
    void showDiceStats();
};

#endif