#ifndef MAEDN_I_JUMP_PAIR_HPP
#define MAEDN_I_JUMP_PAIR_HPP

#include<memory>

class IJumpPair{


    public:
        //IJumpPair(int partnerOne, int partnerTwo);
        /**
         * Check if single is contained in here. If so, returns the partner.
         */
        virtual int getPartnerOrNegative(int single) = 0;
        public:
        virtual int getFirst() = 0;
        virtual int getSecond() = 0;
};
typedef std::shared_ptr<IJumpPair> IJumpPair_SPTR;

#endif