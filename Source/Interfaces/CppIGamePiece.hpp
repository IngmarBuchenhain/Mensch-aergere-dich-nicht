#ifndef MAEDN_I_GAME_PIECE_HPP
#define MAEDN_I_GAME_PIECE_HPP

#include<memory>

#include "CppIGamePieceUI.hpp"

/**
 * Representaton of a game piece. Knows its position as an abstract number and know whether it is in the target area and able to move or finished.
 */ 
class IGamePiece : public IGamePieceUI
{
public:
    /**
     * Sets the position of the GamePiece.
     */
    virtual void setPosition(int fieldNumber) = 0;

public:
    /**
     * Set to target area on specified target area field number.
     * Set isInTargetArea to true;
     */
    virtual void setToTargetArea(int targetAreaFieldNumber) = 0;

public:
    /**
     * Mark this GamePiece as finished.
     */
    virtual void setFinished() = 0;


};

typedef std::shared_ptr<IGamePiece> IGamePiece_SPTR;
//typedef std::unique_ptr<IGamePiece> IGamePiece_UPTR;

#endif