#ifndef MAEDN_CLASS_MAIN_LOGIC_EASY_HPP
#define MAEDN_CLASS_MAIN_LOGIC_EASY_HPP

#include "CppClassMainLogicBase.hpp"

/**
 * The main class/object for running the game.
 * This class contains/knows all needed modules, i.e. UI-object, Network-object and the data.
 * This is the specialized class providing the easy rules.
 * To start the game use the 'startGame'-method.
 */
class MainLogicEasy : public MainLogicBase
{
    /** *************************************
     * Members of MainLogicEasy             *
     * *************************************/

    /** *****************************************
     * Constructors of MainLogicEasy            *
     * *****************************************/

public:
    /**
     * A easy rules game with 4 players, 4 homes and 4 pieces per player.
     */
    MainLogicEasy(IUI_SPTR uiObject);

    /**
     * Individual game with easy rules.
     * numberOfPlayers: 2-6 
     * numberOfHomes: 4/6 (depending on numberOfPlayers)
     * numberOfPieces: 3/4
     */
    MainLogicEasy(IUI_SPTR uiObject, int numberOfHomes, int numberOfPlayers, int numberOfPieces, bool fillWithKI, bool spreadOnBoard, std::vector<std::string> playerNames);

    /** *********************************************
     * Implemented public methods of MainLogicBase  *
     * *********************************************/

public:
    /**
     * Starts the game and represents the application loop running infinitely until the game finished.
     */
    void startGame() override;

    /** *********************************************
     * Implemented private methods of MainLogicBase *
     * *********************************************/

private:
    /**
     * Check if (depending on rules) one player or all players are finished and so the game is finished or not.
     */
    bool gameIsNotFinished() override;

    /**
     * Determine all pieces which are allowed to do a move (depending on rules). 
     * Each piece gets its possible new positions and an indicator whether this new position is in the target area or not.
     * Based on this the user/KI decides which piece to walk.
     */
    std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> getGamePiecesWithNewPositions(int diceRoll, IGamePiece_SPTR lastPiece) override;

    /**
     * Determine (based on rules) whether the currentPlayer is allowed to roll the dice again.
     */
    bool currentPlayerIsAllowedToRollAgain(int currentDiceRoll) override;

    /**
     * Check if in target area the way to the wanted position is free (based on rules).
     */
    bool wayIsFree(int start, int position, int player) override;

    /** *********************************************
     * Private methods of MainLogicDefault          *
     * *********************************************/
};

#endif