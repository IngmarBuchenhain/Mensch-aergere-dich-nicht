#ifndef MAEDN_I_GAME_PIECE_UI_HPP
#define MAEDN_I_GAME_PIECE_UI_HPP

#include <memory>

/**
 * Representaton of a game piece for the UI. 
 * Knows its position as an abstract number and know whether it is in the target area and able to move or finished.
 */
class IGamePieceUI
{
public:
    /**
     * An ID unique to each figure for identification by the UI (and Logic).
     */
    virtual int getID() = 0;

public:
    /**
     * 0: Not on the field yet. Otherwise number between 1 and 'number of fields' or between 1 and 'number of game pieces per player' if in target area.
     */
    virtual int getPosition() = 0;

public:
    /**
     * True if in target area and not able to move any more.
     */
    virtual bool isFinished() = 0;

public:
    /**
     * True if in target area. GamePiece may move anyway because it is for example position 1 of 3 in the target area and 2 and 3 are not used yet.
     */
    virtual bool isInTargetArea() = 0;
};

typedef std::shared_ptr<IGamePieceUI> IGamePieceUI_SPTR;

#endif