#ifndef MAEDN_I_UI_HPP
#define MAEDN_I_UI_HPP

#include <map>
#include <utility>
#include <vector>

#include "CppIGamePieceUI.hpp"
#include "CppIBoardUI.hpp"

#include "CppClassStatistics.hpp"

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
     * Provides information about the board configuration to the UI.
     * Can be used for initialization and for updating while playing.
     */
    virtual void initBoard(IBoardUI_SPTR board) = 0;

public:

    virtual void showInformation(std::string message, std::string color) = 0;
 
public:
    /**
     * Updates the drawn board game with changed game pieces.
     * Must call 'initBoard'-method first!
     */
    virtual void updateBoard(std::vector<std::vector<IGamePieceUI_SPTR>> gamePieces) = 0;


public:
    /**
     * Ask/Make the current player to roll the dice.
     * Does not really produces a number, but simply provides interaction with user and maybe animation..
     */
    virtual void rollDice(std::string currentPlayer, int playerNumber, int diceNumber) = 0;

public:
    /**
     * Present the dice roll of a KI player
     */
    virtual void rollDice(std::string currentPlayer, int diceNumber) = 0;

public:
    /**
     * Present the current player all game pieces he can walk with, and let him choose one.
     * Each piece may have multiple possibilities to walk. The int is the new position, the bool indicates whether the new position is in the target area.
     */
    virtual std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> chooseOneGamePiece(std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces, std::string currentPlayer, int playerNumber, int diceNumberSafe) = 0;

public:
    /**
     * Presents some information to user.
     */
    virtual void showInformation(std::string message) = 0;

public:
    /**
     * Present the winners to the user. Index 0 is first winner, and so on.
     */
    virtual void showWinners(std::vector<std::string> winners) = 0;

public:
    /**
     * Can be used to check if the user wants to export the current game state.
     */
    virtual bool exportIsWanted() = 0;

public:
    /**
     * Can be used to check if the user wants to exit the game.
     */
    virtual bool exitIsWanted() = 0;

public:
    /**
     * Present the given dice statistics to the user.
     */
    virtual void showDiceStats(std::shared_ptr<Statistics> stats) = 0;
};

typedef std::shared_ptr<IUI> IUI_SPTR;

#endif