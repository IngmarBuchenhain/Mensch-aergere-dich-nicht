#ifndef MAEDN_CLASS_MAIN_LOGIC_BASE_HPP
#define MAEDN_CLASS_MAIN_LOGIC_BASE_HPP

#include<map>
#include<utility>
#include "CppDebugHelper.hpp"

#include "CppClassRuleSet.hpp"
#include "CppClassDice.hpp"

#include "CppIGamePiece.hpp"
#include "CppIUI.hpp"
#include "CppClassBoard.hpp"
#include "CppClassGamePiece.hpp"
#include "CppClassStatistics.hpp"
#include "CppIKI.hpp"

/**
 * The main class/object for running the game.
 * This class contains/knows all needed modules, i.e. UI-object, Network-object, and the data.
 * This is the base class. Idea is that this class provides all the needed data. Specialized derived classes implement different rule sets.
 * To start the game use the 'startGame'-method.
 */
class MainLogicBase
{
    /** *************************************
     * Members of MainLogicBase             *
     * *************************************/
    protected:
    // Game configuration
    IBoard_SPTR board; // I need the pointer so I can give the UI the board as pointer to an interface
    RuleSet_UPTR rules;
    Dice_UPTR dice;
    int currentPlayer;
    std::vector<int> winners;
    // UI-object
    IUI_SPTR ui;

    std::unique_ptr<Statistics> stats;
    // Network-object TODO

    // KI-object TODO
    //std::unique_ptr<IKI> ki;
    std::unique_ptr<IKI> kiPlayer[6];

    /** *************************************
     * Constructors of MainLogicBase        *
     * *************************************/

public:
    MainLogicBase();
    /**
     * For instantiation at least an IUI-object is needed.
     * This creates a default game.
     */
    //MainLogicBase(IUI_SPTR uiObject);

public:
    /**
     * Individual game
     * rulesCategory: 0-2
     * numberOfPlayers: 2-6 
     * numberOfHomes: 4/6 (depending on numberOfPlayers)
     * numberOfPieces: 3/4
     */
   // MainLogicBase(IUI_SPTR uiObject, int numberOfHomes, int numberOfPlayers, int numberOfPieces);

    /** *************************************
     * Public methods of MainLogicBase      *
     * *************************************/

public:
    /**
     * Starts the game and represents the application loop running infinitely until the game finished.
     */
    virtual void startGame() = 0;

    /** *************************************
     * Protected methods of MainLogicBase   *
     * *************************************/
protected:
    /**
     * Returns the next player based on the current player.
     * Checks if the choosen player has already finished and if so, takes next player.
     */
    int determineNextPlayer();

    bool playerIsNotFinished(int player);

    void addPlayerToWinnersIfNotPresent(int player);

        int getJumpPosition(int field);

       bool checkIfFree(std::vector<IGamePiece_SPTR> pieces, int position);

       /**
     * 
     */
    void markFinishedPiecesOfTeam(std::vector<IGamePiece_SPTR> &targetAreaPieces);

bool contains(std::vector<int> vector, int containedNumber);
int containsEndField(int start, int steps, int player);

    /**
     * 
     */
    bool currentPlayerHasInHousePieces();

    std::vector<IGamePieceUI_SPTR> convertForUI(std::vector<IGamePiece_SPTR> &origin);
    std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> convertMapForUI(std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> &origin);
    std::vector<IGamePiece_SPTR> convertForLogic(std::vector<IGamePieceUI_SPTR> &origin);
// Checked
    /**
     * Move a game piece of the CURRENT PLAYER on the field to a new position and check if there is a conflict, if so resolve it, based on rules.
     * Check before! whether game piece can walk to this position.
     * 'position' is a fix value, NOT the number of steps to go. So position for the game piece must be determined before based on number of steps.
     * DONT use to walk into target area. Use movePieceInTargetArea-method instead!
     */
    void movePieceOnField(IGamePiece_SPTR piece, int position);

    // Checked
    /**
     * Use to set a game piece of the CURRENT PLAYER to a position in the target area. Doesn't matter if already in there or not. 
     * BUT caution: piece is directly set to this position, no matter if already another piece is there. ->
     * Check before whether the move to this position is valid!
     */
    void movePieceInTargetArea(IGamePiece_SPTR piece, int position);

    // Checked
    /**
     * Check, depending on rules if a game piece already is on this position which causes a conflict.
     */
    IGamePiece_SPTR getConflictGamePiece(int position);




    /**
     * Check if (depending on rules) one player or all players are finished.
     */
    virtual bool gameIsNotFinished() = 0;

    /**
     * 
     */
    virtual bool movePiece(IGamePiece_SPTR piece, int numberOfSteps) = 0;

    

virtual std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> getGamePiecesWithNewPositions(int diceRoll, IGamePiece_SPTR lastPiece) = 0;
//virtual std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> getGamePiecesWithNewPositions(int diceRoll) = 0;
    /**
     * 
     */
    virtual std::vector<IGamePiece_SPTR> determineMoveablePieces(int player) = 0;

    /**
     * 
     */
    //virtual IGamePiece_SPTR MovePieceToStartField(int player) = 0;

    /**
     * 
     */
    //virtual IGamePiece_SPTR checkAndResolveConflict(IGamePiece_SPTR currentPiece) = 0;

    /**
     * 
     */
    //virtual bool movePieceToTargetArea(IGamePiece_SPTR piece, int position) = 0;


    /**
     * 
     */
    //virtual void resolveConflict(IGamePiece_SPTR winner, IGamePiece_SPTR looser) = 0;

    /**
     * 
     */
    virtual IGamePiece_SPTR checkForConflict(IGamePiece_SPTR currentPiece) = 0;

    /**
     * 
     */
   // virtual bool currentPlayerIsAllowedToRollAgain() = 0;

    

     virtual bool currentPlayerIsAllowedToRollAgain(int currentDiceRoll) = 0;



    


    virtual std::vector<IGamePiece_SPTR> determinePossiblePieces(std::vector<IGamePiece_SPTR> &moveablePieces, int numberOfSteps) = 0;
};

#endif