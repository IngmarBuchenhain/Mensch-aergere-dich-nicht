#include "CppClassMainLogicEasy.hpp"
#include "CppDebugHelper.hpp"

#include "CppClassKI.hpp"

#include<iostream>

/** *************************************
 * Constructors of MainLogicEasy        *
 * *************************************/



MainLogicEasy::MainLogicEasy(IUI_SPTR uiObject, std::shared_ptr<GameConfig> config) : MainLogicBase(uiObject, config){
rules = std::make_unique<RuleSet>(false, false, false, true, false, true, false, true, false, false, true, false); // Default

}



/** *************************************
 * Public methods of MainLogicEasy      *
 * *************************************/

/** *************************************
 * Private methods of MainLogicEasy     *
 * *************************************/

std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> MainLogicEasy::getGamePiecesWithNewPositions(int diceRoll, IGamePiece_SPTR lastPiece)
{
    std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> walkAblePieces;
    std::vector<IGamePiece_SPTR> team = board->getTeam(currentPlayer);

    for (int pieceIndex = 0; pieceIndex < team.size(); pieceIndex++)
    {
        // printDebug("Current piece ID to check possibilites");

        IGamePiece_SPTR currentPiece = team[pieceIndex];
        // printDebug(currentPiece->getID());
        // printDebug(currentPiece->getPosition());

        std::vector<std::pair<int, bool>> possibilities;
        if (diceRoll == 6 && currentPiece->getPosition() == 0)
        { // 6 Check
            // Check if startfield free
            // Get startfield
            int start = board->getStartfields()[currentPlayer];
            std::vector<IGamePiece_SPTR> team = board->getTeam(currentPlayer);
     
 std::pair<int, bool> position;
            position.first = start;
            position.second = false;
            possibilities.push_back(position);
           
           
        }
        else
        {
            // No 6 or not an
            // Get possibilities

       
                if (currentPiece->isInTargetArea() && (currentPiece->getPosition() + diceRoll) <= board->getNumberOfGamePiecesPerPlayer() && wayIsFree(currentPiece->getPosition(), currentPiece->getPosition() + diceRoll, currentPlayer))
                {
                    // Check if way is free, if so add
                    printDebug("Is in target area");
                    std::pair<int, bool> position;
                    position.first = currentPiece->getPosition() + diceRoll;
                    printDebug(currentPiece->getPosition() + diceRoll);
                    position.second = true;
                    possibilities.push_back(position);
                }
                else if (!currentPiece->isInTargetArea() && currentPiece->getPosition() != 0)
                {

                    // Check if endField is in range
                    int targetAreaPosition;
                    if ((targetAreaPosition = containsEndField(currentPiece->getPosition(), diceRoll, currentPlayer)) != -1)
                    {
                        printDebug("Going to target area - Number:");
                        printDebug(targetAreaPosition);
                        if (wayIsFree(0, targetAreaPosition, currentPlayer))
                        {
                            std::pair<int, bool> position;
                            position.first = targetAreaPosition;
                            position.second = true;
                            possibilities.push_back(position);
                        }
                    }
                    else
                    {
                        // Get new position
                        printDebug("Normal walk");
                        int newPosition = (currentPiece->getPosition() + diceRoll) % board->getNumberOfFields();
                        if (newPosition == 0)
                        {
                            newPosition = board->getNumberOfFields();
                        }

                        printDebug(newPosition);
                        if (noOwnPieceThere(newPosition))
                        {
                            std::pair<int, bool> position;
                            position.first = newPosition;
                            position.second = false;
                            possibilities.push_back(position);
                        }
                    }
                }

                // If no home area members remained we can walk with this piece. Check possibilities
                // If currentPosition + dicesteps- 1 contains endfield, this can walk into target.
                // Check other possibilities. Forward and backward.
            
        }
        if (possibilities.size() > 0)
        {
            printDebug("Add to walkAblePieces");
            walkAblePieces.insert(std::make_pair(currentPiece, possibilities));
        }
    }

    return walkAblePieces;
}

bool MainLogicEasy::wayIsFree(int start, int position, int player)
{
            if (positionInTargetAreaIsFree(position, player))
            {
                return true;
            }
            return false;


}

bool MainLogicEasy::currentPlayerIsAllowedToRollAgain(int currentDiceRoll)
{
    if (currentDiceRoll == 6)
    {
        return false;
    }
    else
    {
        if (board->getOutsideTeam(currentPlayer).size() == 0 && board->getHomeAreaTeam(currentPlayer).size() > 0)
        {
            return true;
        }
        
    }
    return false;
}

bool MainLogicEasy::gameIsNotFinished()
{

    for (int player = 0; player < board->getNumberOfPlayers(); player++)
    {
        bool allPiecesFinished = true;
        std::vector<IGamePiece_SPTR> team = board->getTeam(player);
        for (int index = 0; index < team.size(); index++)
        {
            if (!team[index]->isFinished())
            {
                allPiecesFinished = false;
            }
        }
        if (allPiecesFinished)
        {

            addPlayerToWinnersIfNotPresent(player);
            return false;
        }
    }
    return true;
}
