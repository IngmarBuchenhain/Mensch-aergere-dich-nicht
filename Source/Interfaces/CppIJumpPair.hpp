#ifndef MAEDN_I_JUMP_PAIR_HPP
#define MAEDN_I_JUMP_PAIR_HPP

#include <memory>

/**
 * Representation of a pair of fields connected into a jump.
 */
class IJumpPair
{

public:
    /**
     * Check if 'single' is contained in here. If so, returns the partner. If not, returns negative (-1) value.
     */
    virtual int getPartnerOrNegative(int single) = 0;

public:
    /**
     * Get first of the pair. May not be the first in numerical order.
     */
    virtual int getFirst() = 0;

public:
    /**
     * Get second of the pair. May not be the second in numerical order.
     */
    virtual int getSecond() = 0;
};

typedef std::shared_ptr<IJumpPair> IJumpPair_SPTR;

#endif