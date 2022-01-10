#ifndef MAEDN_CLASS_MAIN_LOGIC_BASE_HPP
#define MAEDN_CLASS_MAIN_LOGIC_BASE_HPP

#include <map>
#include <utility>

#include "CppIUI.hpp"
#include "CppIKI.hpp"

#include "CppClassRuleSet.hpp"
#include "CppClassDice.hpp"
#include "CppClassBoard.hpp"
#include "CppClassGamePiece.hpp"
#include "CppClassStatistics.hpp"
#include "CppStructsForConfigAndState.hpp"

/**
 * The main class/object for running the game logic.
 * This class contains/knows all needed modules, i.e. UI-object, Network-object and the data.
 * This is the base class. Idea is that this class provides all the needed data and methods used in every RuleSet. Specialized derived classes implement different RuleSet with more complexity.
 * To start the game use the 'startGame'-method.
 */
class MainLogicBase
{
    /** *************************************
     * Members of MainLogicBase             *
     * *************************************/

protected:
    // Game configuration
    IBoard_SPTR board;  // I need the shared pointer so I can give the UI the board as pointer to an interface.
    RuleSet_UPTR rules; // I only need unique pointer as I only use it in here.
    Dice_UPTR dice;
    int currentPlayer;
    IGamePiece_SPTR lastGamePiece = nullptr;
    std::vector<int> winners; // May be one or if played until all finished multiple.
    std::vector<std::string> nameOfPlayers;

    /**
     * UI-object
     * For communication with user
     */
    IUI_SPTR ui; // I need the shared pointer as it is given in constructor from outside.

    /** 
     * Stat-object
     * Holds some dice statistics.
     */
    std::shared_ptr<Statistics> stats;
    std::shared_ptr<GameConfig> config;

    /**
     * KI-objects
     * Used to determine whether a player is human or KI and if so, get the KI-object. 
     * Index is the KI of the Index-player. If it is nullptr it is a human player.
     */
    std::shared_ptr<IKI> kiPlayer[6];

    /** *************************************
     * Constructors of MainLogicBase        *
     * *************************************/

    /**
     * Individual game with default rules.
     * numberOfPlayers: 2-6 
     * numberOfHomes: 4/6 (depending on numberOfPlayers)
     * numberOfPieces: 3/4
     */
    MainLogicBase(IUI_SPTR uiObject, std::shared_ptr<GameConfig> config);

    /** *********************************************
     * Public methods of MainLogicBase              *
     * *********************************************/

public:
    /**
     * Starts the game and represents the application loop running infinitely until the game finished.
     */
    void startGame();


    /**
     * Use before startGame() if you want to load a game state. Number of pieces must fit to number of pieces in the game.
     */
    void importGameState(std::vector<std::shared_ptr<GamePieceState>> &piecesState, int player, int lastPiece, std::shared_ptr<Statistics> statistics);
protected:
void exportGameState();
    /** *********************************************
     * Virtual protected methods of MainLogicBase   *
     * *********************************************/

protected:


    /**
     * Check if (depending on rules) one player or all players are finished and so the game is finished or not.
     */
    virtual bool gameIsNotFinished() = 0;

    /**
     * Check if in target area the way to the wanted position is free (based on rules).
     */
    virtual bool wayIsFree(int start, int position, int player) = 0;

    /**
     * Determine all pieces which are allowed to do a move (depending on rules). 
     * Each piece gets its possible new positions and an indicator whether this new position is in the target area or not.
     * Based on this the user/KI decides which piece to walk.
     */
    virtual std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> getGamePiecesWithNewPositions(int diceRoll, IGamePiece_SPTR lastPiece) = 0;

    /**
     * Determine (based on rules) whether the currentPlayer is allowed to roll the dice again.
     */
    virtual bool currentPlayerIsAllowedToRollAgain(int currentDiceRoll) = 0;

    /** *************************************
     * Protected methods of MainLogicBase   *
     * *************************************/

protected:
IGamePiece_SPTR getGamePieceToID(int id);
    /**
     * Returns the next player based on the current player.
     * Checks if the choosen player has already finished and if so, takes next player.
     */
    int determineNextPlayer();

    /**
     * Check if a specified player is finished or not.
     */
    bool playerIsNotFinished(int player);

    /**
     * Add a player to the winner board, if not already on it.
     */
    void addPlayerToWinnersIfNotPresent(int player);

    /**
     * Determine the field on which to jump from the given field.
     * If the given field is not a jump field, returns a negative value.
     */
    int getJumpPosition(int field);

    /**
     * Check if on a specific position already a piece is standing.
     */
    bool checkIfFree(std::vector<IGamePiece_SPTR> pieces, int position);

    /**
     * Check pieces in target area.
     * If they are finished, mark them.
     */
    void markFinishedPiecesOfTeam(std::vector<IGamePiece_SPTR> &targetAreaPieces);

    /**
     * Check if a given vector contains a given number.
     */
    bool contains(std::vector<int> vector, int containedNumber);

    /**
     * Check if the endField of a given player is between the 'start' field and a number of given steps.
     */
    int containsEndField(int start, int steps, int player);

    /**
     * Check if a specified position in target area of a player is free.
     */
    bool positionInTargetAreaIsFree(int field, int player);

    /**
     * Check if on the given position is no own piece of the current player.
     */
    bool noOwnPieceThere(int newPosition);

    /**
     * Helper to convert between GamePiece interfaces
     */
    std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> convertMapForUI(std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> &origin);

    /**
     * Check, depending on rules if a game piece already is on this position which causes a conflict.
     */
    IGamePiece_SPTR getConflictGamePiece(int position);

    /**
     * Move a game piece of the CURRENT PLAYER on the field to a new position and check if there is a conflict, if so resolve it, based on rules.
     * Check before! whether game piece can walk to this position.
     * 'position' is a fix value, NOT the number of steps to go. So position for the game piece must be determined before based on number of steps.
     * DONT use to walk into target area. Use movePieceInTargetArea-method instead!
     */
    void movePieceOnField(IGamePiece_SPTR piece, int position);

    /**
     * Use to set a game piece of the CURRENT PLAYER to a position in the target area. Doesn't matter if already in there or not. 
     * BUT caution: piece is directly set to this position, no matter if already another piece is there. ->
     * Check before whether the move to this position is valid!
     */
    void movePieceInTargetArea(IGamePiece_SPTR piece, int position);
};

#endif