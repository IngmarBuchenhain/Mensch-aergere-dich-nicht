#ifndef MAEDN_CLASS_MAIN_LOGIC_HPP
#define MAEDN_CLASS_MAIN_LOGIC_HPP

#include "CppDebugHelper.hpp"

#include "CppClassRuleSet.hpp"
#include "CppClassDice.hpp"

#include "CppIGamePiece.hpp"
#include "CppIBoard.hpp"
#include "CppIUI.hpp"

/**
 * The main class/object for running the game.
 * This class contains/knows all needed modules, i.e. UI-object, Network-object, and the data.
 * Default constructor creates a boring default game.
 * To start the game use the 'startGame'-method.
 */
class MainLogic
{
    /** *************************************
     * Members of MainLogic                 *
     * *************************************/

    // Game configuration
    IBoard_SPTR board;  // I need the pointer so I can give the UI the board as pointer to an interface
    RuleSet_UPTR rules;
    Dice_UPTR dice;
    int currentPlayer;

    // UI-object
    IUI_SPTR ui;

    // Network-object TODO

    // KI-object TODO


    /** *************************************
     * Constructors of MainLogic            *
     * *************************************/


public:
    /**
     * For instantiation at least an IUI-object is needed.
     * This creates a default game.
     */
    MainLogic(IUI_SPTR uiObject);

public:
    /**
     * Individual game
     * rulesCategory: 0-2
     * numberOfPlayers: 2-6 
     * numberOfHomes: 4/6 (depending on numberOfPlayers)
     * numberOfPieces: 3/4
     */
    MainLogic(IUI_SPTR uiObject, int rulesCategory, int numberOfHomes, int numberOfPlayers, int numberOfPieces);


    /** *************************************
     * Public methods of MainLogic          *
     * *************************************/


public:
    /**
     * Starts the game and represents the application loop running infinitely until the game finished.
     */
    void startGame();


    /** *************************************
     * Private methods of MainLogic         *
     * *************************************/


    /**
     * Randomly returns a number out of the number of players.
     * Here the real number is wanted. So for 3 players its 3.
     * Internally we start counting with 0. So a number between 0 and 2 is returned.
     */
    int determineStartPlayer(int numberOfPlayers);

    /**
     * Returns the next player based on the current player.
     * Checks if the choosen player has already finished and if so, takes next player.
     */
    int determineNextPlayer();

    /**
     * Check if (depending on rules) one player or all players are finished.
     */
    bool gameIsNotFinished();

    /**
     * 
     */
    bool movePiece(IGamePiece_SPTR piece, int numberOfSteps);

    /**
     * 
     */
    std::vector<IGamePiece_SPTR> determineMoveablePieces(int player);

    /**
     * 
     */
    IGamePiece_SPTR MovePieceToStartField(int player);

    /**
     * 
     */
    IGamePiece_SPTR checkAndResolveConflict(IGamePiece_SPTR currentPiece);
    
    /**
     * 
     */
    bool movePieceToTargetArea(IGamePiece_SPTR piece, int position);

    /**
     * 
     */   
    bool currentPlayerHasInHousePieces();
    
    /**
     * 
     */
    void resolveConflict(IGamePiece_SPTR winner, IGamePiece_SPTR looser);
    
    /**
     * 
     */
    IGamePiece_SPTR checkForConflict(IGamePiece_SPTR currentPiece);

    /**
     * 
     */
    bool currentPlayerIsAllowedToRollAgain();

    /**
     * 
     */
    void markFinishedPiecesOfTeam(std::vector<IGamePiece_SPTR> &targetAreaPieces);
};

#endif