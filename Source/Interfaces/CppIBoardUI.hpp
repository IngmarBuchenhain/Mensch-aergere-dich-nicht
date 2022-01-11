#ifndef MAEDN_I_BOARD_UI_HPP
#define MAEDN_I_BOARD_UI_HPP

#include <vector>
#include <memory>

#include "CppIGamePieceUI.hpp"
#include "CppIJumpPair.hpp"

/**
 * Use within UI. Representation of the game board, including game pieces.
 */
class IBoardUI
{
public:
    /**
     * Right now two boards are provided with 40 or 48 fields.
     */
    virtual int getNumberOfFields() = 0;

public:
    /**
     * This returns human and KI players, so 1-6.
     */
    virtual int getNumberOfPlayers() = 0;

public:
    /**
     * 3/4 are supported right now.
     */
    virtual int getNumberOfGamePiecesPerPlayer() = 0;

public:
    /**
     * Correlates with getNumberOfFields. 4/6 homes are provided by the two board sizes.
     */
    virtual int getNumberOfHomes() = 0;

public:
    /**
     * Return a vector, containing the start fields of all players. Player 0 has index 0 in vector and so on.
     */
    virtual std::vector<int> getStartfields() = 0;

public:
    /**
     * Return a vector, containing the end fields of all players. Player 0 has index 0 in vector and so on.
     */
    virtual std::vector<int> getEndFields() = 0;

public:
    /**
     * Return a vector with all pairs of jumping fields.
     */
    virtual std::vector<IJumpPair_SPTR> getJumpFields() = 0;

public:
    /**
     * All game pieces in a vector. Outer vector is at index 0 pieces of player 0. Inner vector contains all game pieces of one player.
     */
    virtual std::vector<std::vector<IGamePieceUI_SPTR>> getGamePieces() = 0;
};

typedef std::shared_ptr<IBoardUI> IBoardUI_SPTR;

#endif