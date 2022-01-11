#ifndef MAEDN_CLASS_DICE_HPP
#define MAEDN_CLASS_DICE_HPP

// Used CppRandom.hpp from lecture and modified it for MAEDN.

#include <memory>

/**
 * Represents a dice with values from 1 to 6.
 */
class Dice
{
public:
    /**
     * Roll the dice and return a number between 1 and 6 (including).
     */
    int roll();

public:
    /**
     * Returns one number out of 0 to 'numberOfPlayers'-1.
     */
    int getStartPlayer(int numberOfPlayers);
};

typedef std::unique_ptr<Dice> Dice_UPTR;

#endif