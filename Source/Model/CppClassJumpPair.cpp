#include "CppClassJumpPair.hpp"

JumpPair::JumpPair(int partnerOne, int partnerTwo)
{
    x = partnerOne;
    y = partnerTwo;
}

int JumpPair::getPartnerOrNegative(int single)
{
    if (x == single)
    {
        return y;
    }
    else if (y == single)
    {
        return x;
    }
    else
    {
        return -1;
    }
}

int JumpPair::getFirst()
{
    return x;
}

int JumpPair::getSecond()
{
    return y;
}