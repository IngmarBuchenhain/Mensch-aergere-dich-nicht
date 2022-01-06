#ifndef MAEDN_CLASS_GAME_PIECE_HPP
#define MAEDN_CLASS_GAME_PIECE_HPP

#include "CppIGamePiece.hpp"
//#include "CppIGamePieceUI.hpp"

/**
 * Representaton of a game piece. Knows its position as an abstract number and know whether it is in the target area and able to move or finished.
 */ 
class GamePiece : public IGamePiece
{
    // 0 or greater. Unique to each GamePiece. Never alter this!
    int id;
    // 0 or greater. The one who sets this value is responsible that the position is valid to the game this GamePiece is in.
    int position = 0;
    // True if in target area and not able to move any more.
    bool finished = false;
    // True if in target area. GamePiece may move anyway because it is for example position 1 of 3 in the target area and 2 and 3 are not used yet.
    bool inTargetArea = false;

public:
    /**
     * An ID unique to each figure for identification by the UI.
     */
    int getID() override;

public:
    /**
     * 0: Not on the field yet. Otherwise number between 1 and 'number of fields' or between 1 and 'number of game pieces per player'.
     */
    int getPosition() override;

public:
    /**
     * True if in target area and not able to move any more.
     */
    bool isFinished() override;

public:
    /**
     * True if in target area. GamePiece may move anyway because it is for example position 1 of 3 in the target area and 2 and 3 are not used yet.
     */
    bool isInTargetArea() override;

public:
    /**
     * Sets the position of the GamePiece.
     */
    void setPosition(int fieldNumber) override;

public:
    /**
     * Set to target area on specified target area field number.
     * Set isInTargetArea to true;
     */
    void setToTargetArea(int targetAreaFieldNumber) override;

public:
    /**
     * Mark this GamePiece as finished.
     */
    void setFinished() override;

public:
    /**
     * Default constructor
     */
    GamePiece();
};

#endif