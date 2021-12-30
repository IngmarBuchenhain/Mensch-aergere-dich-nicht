#ifndef MAEDN_I_BOARD_UI_HPP
#define MAEDN_I_BOARD_UI_HPP

#include <vector>
#include <memory>

#include "CppIGamePieceUI.hpp"
#include "CppIJumpPair.hpp"


/**
 * Representation of the board for use with the ui.
 */
class IBoardUI
{
public:
    // 40 oder 48
    virtual int getNumberOfFields() = 0;

public:
// 2-6
    virtual int getNumberOfPlayers() = 0;

public:
    virtual int getNumberOfGamePiecesPerPlayer() = 0;

public:
//4/6
    virtual int getNumberOfHomes() = 0;

    virtual std::vector<int> getStartfields() = 0;
    public:
    virtual std::vector<int> getEndFields() = 0;
    public:
    virtual std::vector<IJumpPair_SPTR> getJumpFields() = 0;

public:
    virtual std::vector<std::vector<IGamePieceUI_SPTR>> getGamePieces() = 0;




};

typedef std::shared_ptr<IBoardUI> IBoardUI_SPTR;
//typedef std::unique_ptr<IBoardUI> IBoardUI_UPTR;

#endif