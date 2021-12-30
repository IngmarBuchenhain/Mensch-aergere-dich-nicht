#ifndef MAEDN_I_BOARD_STATE_HPP
#define MAEDN_I_BOARD_STATE_HPP

#include<vector>

#include "CppIGamePiece.hpp"
#include "CppIField.hpp"

/**
 * 
 */
class IBoardState
{
public:
    virtual std::vector<IField> getFields() = 0;

public:
    virtual std::vector<IGamePiece> getGamePieces() = 0;

public:
    virtual int getCurrentPlayer() = 0;
};

#endif