// Used CppRandom.hpp from lecture and modified it for MAEDN.
#ifndef MAEDN_CLASS_DICE_HPP
#define MAEDN_CLASS_DICE_HPP

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
    int getStartPlayer(int numberOfPlayers);

public:
    /**
     * Default constructor.
     */
    Dice();
};

typedef std::unique_ptr<Dice> Dice_UPTR;

#endif