#ifndef MAEDN_CLASS_MAIN_LOGIC_DEFAULT_HPP
#define MAEDN_CLASS_MAIN_LOGIC_DEFAULT_HPP

#include "CppClassMainLogicBase.hpp"

/**
 * The main class/object for running the game.
 * This class contains/knows all needed modules, i.e. UI-object, Network-object, and the data.
 * This is the specialized class providing the default rules.
 * To start the game use the 'startGame'-method.
 */
class MainLogicDefault : public MainLogicBase{
    public:
    MainLogicDefault(IUI_SPTR uiObject);
    MainLogicDefault(IUI_SPTR uiObject, int numberOfHomes, int numberOfPlayers, int numberOfPieces);

    /** ****************************************
     * Implemented methods of MainLogicDefault *
     * *****************************************/

    public:
    void startGame() override;


    private:
    /**
     * Check if (depending on rules) one player or all players are finished.
     */
   bool gameIsNotFinished() override;

    /**
     * 
     */
     bool movePiece(IGamePiece_SPTR piece, int numberOfSteps) override;
bool noOwnPieceThere(int newPosition);
    


std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> getGamePiecesWithNewPositions(int diceRoll, IGamePiece_SPTR lastPiece) override;
    /**
     * 
     */
    std::vector<IGamePiece_SPTR> determineMoveablePieces(int player) override;

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
     void resolveConflict(IGamePiece_SPTR winner, IGamePiece_SPTR looser);

    /**
     * 
     */
     IGamePiece_SPTR checkForConflict(IGamePiece_SPTR currentPiece) override;

    /**
     * 
     */
     bool currentPlayerIsAllowedToRollAgain(int currentDiceRoll) override;

    

    



    


    std::vector<IGamePiece_SPTR> determinePossiblePieces(std::vector<IGamePiece_SPTR> &moveablePieces, int numberOfSteps) override;
    bool positionIsFree(int field, int player);
    bool wayIsFree(int start, int position, int player);





    
};

#endif