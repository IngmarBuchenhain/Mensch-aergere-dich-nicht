#ifndef MAEDN_I_GAME_PIECE_HPP
#define MAEDN_I_GAME_PIECE_HPP

#include "CppIField.hpp"

class IGamePiece
{
public:
    virtual int getTeam() = 0;

public:
    virtual IField getPosition() = 0;
};

#endif