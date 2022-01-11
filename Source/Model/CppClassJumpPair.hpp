#ifndef MAEDN_CLASS_JUMP_PAIR_HPP
#define MAEDN_CLASS_JUMP_PAIR_HPP

#include "CppIJumpPair.hpp"

class JumpPair : public IJumpPair
{
    int x;
    int y;

public:
    JumpPair(int partnerOne, int partnerTwo);

public:
    /**
     * Check if 'single' is contained in here. If so, returns the partner. If not, returns negative (-1) value.
     */
    int getPartnerOrNegative(int single) override;

public:
    /**
     * Get first of the pair. May not be the first in numerical order.
     */
    int getFirst() override;

public:
    /**
     * Get second of the pair. May not be the second in numerical order.
     */
    int getSecond() override;
};

#endif