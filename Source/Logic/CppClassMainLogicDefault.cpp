#include "CppClassMainLogicDefault.hpp"

/** *************************************
 * Constructors of MainLogicDefault     *
 * *************************************/

MainLogicDefault::MainLogicDefault(IUI_SPTR uiObject, std::shared_ptr<GameConfig> config) : MainLogicBase(uiObject, config)
{
    rules = std::make_unique<RuleSet>(); // Default
}

/** *************************************
 * Public methods of MainLogicDefault   *
 * *************************************/

/** *************************************
 * Private methods of MainLogicDefault  *
 * *************************************/

std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> MainLogicDefault::getGamePiecesWithNewPositions(int diceRoll, IGamePiece_SPTR lastPiece)
{
    std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> walkAblePieces;
    std::vector<IGamePiece_SPTR> team = board->getTeam(currentPlayer);
    bool alreadyFinished = false;

    // check the whole team for walkable pieces
    for (int pieceIndex = 0; pieceIndex < team.size(); pieceIndex++)
    {
        IGamePiece_SPTR currentPiece = team[pieceIndex];

        if (alreadyFinished)
        {
            break;
        }
        if (lastPiece != nullptr)
        { // We have to take the same piece. So set the last piece to the one we determine position and note that we are finished after thate.
            printDebug("Take same piece");

            currentPiece = lastPiece;
            alreadyFinished = true;
        }
        std::vector<std::pair<int, bool>> possibilities;
        if (diceRoll == 6 && currentPiece->getPosition() == 0)
        { // 6 Check
            // Check if startfield free
            // Get startfield
            int start = board->getStartfields()[currentPlayer];
            std::vector<IGamePiece_SPTR> team = board->getTeam(currentPlayer);
            if (checkIfFree(team, start))
            {
                std::pair<int, bool> position;
                position.first = start;
                position.second = false;
                possibilities.push_back(position);
            }
        }
        else
        {
            // No 6 or not a home piece
            // Get possibilities
            bool getPossibilities = true;
            if (diceRoll == 6 && board->getHomeAreaTeam(currentPlayer).size() != 0)
            {
                // If we have a six and we have home pieces, we do not search longer for this piece, as it is not allowed to walk.
                getPossibilities = false;
            }
            if (getPossibilities)
            {
                if (currentPiece->isInTargetArea() && (currentPiece->getPosition() + diceRoll) <= board->getNumberOfGamePiecesPerPlayer() && wayIsFree(currentPiece->getPosition(), currentPiece->getPosition() + diceRoll, currentPlayer))
                { // If in target area, check if we can walk.
                    // Check if way is free, if so add and note that we are in target area.
                    printDebug("Is in target area");
                    std::pair<int, bool> position;
                    position.first = currentPiece->getPosition() + diceRoll;
                    printDebug(currentPiece->getPosition() + diceRoll);
                    position.second = true;
                    possibilities.push_back(position);
                }
                else if (!currentPiece->isInTargetArea() && currentPiece->getPosition() != 0)
                {
                    // If it is a field piece, check if we can go to the target area.
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
                        if (!waitBeforeEndField(currentPiece->getPosition(), diceRoll, currentPlayer))
                        { // Check if we can wait before the target area, if so we don't have to walk. But when in here, we can walk so check the new position out.
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
                }
            }
        }
        if (possibilities.size() > 0)
        {
            printDebug("Add to walkAblePieces");
            walkAblePieces.insert(std::make_pair(currentPiece, possibilities));
        }
    }
    return walkAblePieces;
}

bool MainLogicDefault::wayIsFree(int start, int position, int player)
{
    std::vector<IGamePiece_SPTR> team = board->getTeam(player);
    for (int index = 0; index < team.size(); index++)
    {
        for (int posIndex = start + 1; posIndex <= position; posIndex++)
        {
            if (!positionInTargetAreaIsFree(posIndex, player))
            {
                return false;
            }
        }
    }
    return true;
}

bool MainLogicDefault::currentPlayerIsAllowedToRollAgain(int currentDiceRoll)
{
    if (currentDiceRoll == 6)
    {
        return false;
    }
    else
    {
        if (board->getOutsideTeam(currentPlayer).size() == 0 && board->getHomeAreaTeam(currentPlayer).size() > 0)
        {
            // Check if someone in target area can walk
            if (targetAreaMemberOfCurrentPlayerCanWalk(currentDiceRoll))
            {
                return false;
            }
            return true;
        }
    }
    return false;
}

bool MainLogicDefault::targetAreaMemberOfCurrentPlayerCanWalk(int diceRoll)
{
    std::vector<IGamePiece_SPTR> targetTeam = board->getTargetAreaTeam(currentPlayer);
    for (int index = 0; index < targetTeam.size(); index++)
    {
        int targetPosition = targetTeam[index]->getPosition() + diceRoll;
        if (targetPosition <= board->getNumberOfGamePiecesPerPlayer() && wayIsFree(targetTeam[index]->getPosition(), targetPosition, currentPlayer))
        {
            return true;
        }
    }
    return false;
}

bool MainLogicDefault::gameIsNotFinished()
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
