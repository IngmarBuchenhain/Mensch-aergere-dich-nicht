// Used CppRandom.hpp from lecture and modified it for MAEDN.
#ifndef MAEDN_CLASS_DICE_HPP
#define MAEDN_CLASS_DICE_HPP

#include <random>
#include <memory>

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
     * Default constructor.
     */
    Dice();
};

typedef std::unique_ptr<Dice> Dice_UPTR;

#endif