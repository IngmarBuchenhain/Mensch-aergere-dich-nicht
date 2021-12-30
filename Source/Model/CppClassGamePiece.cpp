#include "CppClassGamePiece.hpp"

// Implementation of GamePiece:
// Representaton of a game piece. Knows its position as an abstract number and know whether it is in the target area and able to move or finished.
int GamePiece::getID(){
    return id;
}

int GamePiece::getPosition()
{
    return position;
}

bool GamePiece::isFinished()
{
    return finished;
}

bool GamePiece::isInTargetArea()
{
    return inTargetArea;
}

void GamePiece::setPosition(int fieldNumber)
{
    if(!inTargetArea){
        position = fieldNumber;
    } else {
        // Throw Exception
    }
    
}

void GamePiece::setToTargetArea(int targetAreaFieldNumber)
{
    inTargetArea = true;
    position = targetAreaFieldNumber;
}

void GamePiece::setFinished()
{
    finished = true;
}

GamePiece::GamePiece(){
    id = GLOBAL_I_GAME_PIECE_ID_COUNTER;
    GLOBAL_I_GAME_PIECE_ID_COUNTER++;
}
