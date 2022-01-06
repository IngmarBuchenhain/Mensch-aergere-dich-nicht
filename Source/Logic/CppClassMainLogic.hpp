// #ifndef MAEDN_CLASS_MAIN_LOGIC_HPP
// #define MAEDN_CLASS_MAIN_LOGIC_HPP

// #include<map>
// #include<utility>
// #include "CppDebugHelper.hpp"

// #include "CppClassRuleSet.hpp"
// #include "CppClassDice.hpp"

// #include "CppIGamePiece.hpp"
// //#include "CppIBoard.hpp"
// #include "CppIUI.hpp"
// #include "CppClassBoard.hpp"
// #include "CppClassGamePiece.hpp"

// /**
//  * The main class/object for running the game.
//  * This class contains/knows all needed modules, i.e. UI-object, Network-object, and the data.
//  * Default constructor creates a boring default game.
//  * To start the game use the 'startGame'-method.
//  */
// class MainLogic
// {
//     /** *************************************
//      * Members of MainLogic                 *
//      * *************************************/

//     // Game configuration
//     IBoard_SPTR board; // I need the pointer so I can give the UI the board as pointer to an interface
//     RuleSet_UPTR rules;
//     Dice_UPTR dice;
//     int currentPlayer;
//     std::vector<int> winners;
//     // UI-object
//     IUI_SPTR ui;

//     // Network-object TODO

//     // KI-object TODO

//     /** *************************************
//      * Constructors of MainLogic            *
//      * *************************************/

// public:
//     /**
//      * For instantiation at least an IUI-object is needed.
//      * This creates a default game.
//      */
//     MainLogic(IUI_SPTR uiObject);

// public:
//     /**
//      * Individual game
//      * rulesCategory: 0-2
//      * numberOfPlayers: 2-6 
//      * numberOfHomes: 4/6 (depending on numberOfPlayers)
//      * numberOfPieces: 3/4
//      */
//     MainLogic(IUI_SPTR uiObject, int rulesCategory, int numberOfHomes, int numberOfPlayers, int numberOfPieces);

//     /** *************************************
//      * Public methods of MainLogic          *
//      * *************************************/

// public:
//     /**
//      * Starts the game and represents the application loop running infinitely until the game finished.
//      */
//     void startGame();

//     /** *************************************
//      * Private methods of MainLogic         *
//      * *************************************/

//     /**
//      * Randomly returns a number out of the number of players.
//      * Here the real number is wanted. So for 3 players its 3.
//      * Internally we start counting with 0. So a number between 0 and 2 is returned.
//      */
//     //int determineStartPlayer(int numberOfPlayers);

//     /**
//      * Returns the next player based on the current player.
//      * Checks if the choosen player has already finished and if so, takes next player.
//      */
//     int determineNextPlayer();

//     /**
//      * Check if (depending on rules) one player or all players are finished.
//      */
//     bool gameIsNotFinished();

//     /**
//      * 
//      */
//     bool movePiece(IGamePiece_SPTR piece, int numberOfSteps);

//     // Checked
//     /**
//      * Move a game piece of the CURRENT PLAYER on the field to a new position and check if there is a conflict, if so resolve it, based on rules.
//      * Check before! whether game piece can walk to this position.
//      * 'position' is a fix value, NOT the number of steps to go. So position for the game piece must be determined before based on number of steps.
//      * DONT use to walk into target area. Use movePieceInTargetArea-method instead!
//      */
//     void movePieceOnField(IGamePiece_SPTR piece, int position);

//     // Checked
//     /**
//      * Use to set a game piece of the CURRENT PLAYER to a position in the target area. Doesn't matter if already in there or not. 
//      * BUT caution: piece is directly set to this position, no matter if already another piece is there. ->
//      * Check before whether the move to this position is valid!
//      */
//     void movePieceInTargetArea(IGamePiece_SPTR piece, int position);

//     // Checked
//     /**
//      * Check, depending on rules if a game piece already is on this position which causes a conflict.
//      */
//     IGamePiece_SPTR getConflictGamePiece(int position);


// std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> getGamePiecesWithNewPositions(int diceRoll);
//     /**
//      * 
//      */
//     std::vector<IGamePiece_SPTR> determineMoveablePieces(int player);

//     /**
//      * 
//      */
//     IGamePiece_SPTR MovePieceToStartField(int player);

//     /**
//      * 
//      */
//     IGamePiece_SPTR checkAndResolveConflict(IGamePiece_SPTR currentPiece);

//     /**
//      * 
//      */
//     bool movePieceToTargetArea(IGamePiece_SPTR piece, int position);

//     /**
//      * 
//      */
//     bool currentPlayerHasInHousePieces();

//     /**
//      * 
//      */
//     void resolveConflict(IGamePiece_SPTR winner, IGamePiece_SPTR looser);

//     /**
//      * 
//      */
//     IGamePiece_SPTR checkForConflict(IGamePiece_SPTR currentPiece);

//     /**
//      * 
//      */
//     bool currentPlayerIsAllowedToRollAgain();

//     /**
//      * 
//      */
//     void markFinishedPiecesOfTeam(std::vector<IGamePiece_SPTR> &targetAreaPieces);
//     bool playerIsNotFinished(int player);

//     int getJumpPosition(int field);

//     void addPlayerToWinnersIfNotPresent(int player);

//     std::vector<IGamePieceUI_SPTR> convertForUI(std::vector<IGamePiece_SPTR> &origin);
//     std::vector<IGamePiece_SPTR> convertForLogic(std::vector<IGamePieceUI_SPTR> &origin);

//     std::vector<IGamePiece_SPTR> determinePossiblePieces(std::vector<IGamePiece_SPTR> &moveablePieces, int numberOfSteps);
// };

// #endif