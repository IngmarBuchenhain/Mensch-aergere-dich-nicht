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
         * Check if single is contained in here. If so, returns the partner.
         */
    int getPartnerOrNegative(int single) override;

public:
    int getFirst() override;
    int getSecond() override;
};

#endif