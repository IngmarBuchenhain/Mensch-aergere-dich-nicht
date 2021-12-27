#ifndef MAEDN_I_UI_HPP
#define MAEDN_I_UI_HPP

#include "CppIGamePiece.hpp"
#include "CppIBoardState.hpp"

/**
 * Main UI-Interface
 * Used by logic class (gets an IUI-object in constructor) to present the data and initialize interaction with user.
 * All interaction/presentation with user only happens via this interface (except debugging).
 * Designed for CLI, but may be extendable for GUI also.
 * Must not contain any game logic or data (except some caching or drawable/changeable UI-objects).
 * Provides methods and logic for presenting/updating the data given by logic-class 
 * and for interactions with user initialized by logic-class.
 */
class IUI
{
public:
    /**
     * Draws/Presents the whole board with game pieces.
     * Provides basic information about the board configuration to the UI.
     * Can be used for initialization and for updating while playing.
     */
    virtual void initBoard(IBoardState currentBoard) = 0;

public:
    /**
     * Presents some information to user.
     */
    virtual void showInformation(std::string message) = 0;

public:
    /**
     * Presents the given number to the user.
     */
    virtual void showDice(int diceNumber) = 0;

public:
    /**
     * Ask/Make the current player to roll the dice.
     * Does not real produces a number, but simply provides interaction with user and maybe animation..
     */
    virtual void rollDice(std::string currentPlayer) = 0;

public:
    /**
     * Present the current player all game pieces he can walk with, and let him choose one.
     */
    virtual IGamePiece chooseGamePiece(std::vector<IGamePiece> &gamePieces, std::string currentPlayer) = 0;

public:
    /**
     * Updates the drawn board game with changed game pieces.
     * Must call 'initBoard'-method first!
     * Throws exception if no board was initialized!
     */
    virtual bool updateBoard(std::vector<IGamePiece> &gamePieces) = 0;
};

#endif