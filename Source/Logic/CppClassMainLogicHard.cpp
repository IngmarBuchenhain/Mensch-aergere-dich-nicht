#include "CppClassMainLogicHard.hpp"
#include <iostream>
/** *************************************
 * Constructors of MainLogicHard        *
 * *************************************/

MainLogicHard::MainLogicHard(IUI_SPTR uiObject, std::shared_ptr<GameConfig> config) : MainLogicBase(uiObject, config)
{
    rules = std::make_unique<RuleSet>(true, true, true, false, true, false, true, false, true, true, false, true); // Hard
}

/** *************************************
 * Private methods of MainLogicHard     *
 * *************************************/

std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> MainLogicHard::getGamePiecesWithNewPositions(int diceRoll, IGamePiece_SPTR lastPiece)
{
    // Have to possibilities: One if we can not throw, one if we can (and must) throw.
    std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> walkAblePieces;
    std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> walkAblePiecesThrowing;

    std::vector<IGamePiece_SPTR> team = board->getTeam(currentPlayer);
    bool alreadyFinished = false;
    bool notOnlyThrowsAllowed = true;

    // Check if someone is on the startfield of the team. If so we have to free it. We can not walk with another piece as long as it is not freed.
    bool mustfreeStartField = false;
    if (pieceOnStartField())
    {
        mustfreeStartField = true;
    }

    // Check whole team
    for (int pieceIndex = 0; pieceIndex < team.size(); pieceIndex++)
    {
        IGamePiece_SPTR currentPiece = team[pieceIndex];

        if (mustfreeStartField && (currentPiece->getPosition() != board->getStartfields()[currentPlayer] || currentPiece->isInTargetArea()))
        {
            continue;
        }

        if (alreadyFinished)
        {
            break;
        }
        if (lastPiece != nullptr)
        {
            printDebug("Take same piece");
            // We have to walk with the same piece again. So no need to check other pieces.
            currentPiece = lastPiece;
            alreadyFinished = true;
        }
        std::vector<std::pair<int, bool>> possibilities;
        std::vector<std::pair<int, bool>> possibilitiesThrow;

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
            if (currentPiece->getPosition() == 0)
            {
                continue;
            }
            // No 6 or not a home piece
            // Get possibilities
            bool getPossibilities = true;
            if (diceRoll == 6 && board->getHomeAreaTeam(currentPlayer).size() != 0)
            {
                getPossibilities = false;
            }
            if (getPossibilities)
            {
                // First check if we can throw someone. If so, this is the only action. If not, do the normal stuff.
                int forwardPosition;
                int backwardPosition;

                if (!currentPiece->isInTargetArea())
                {
                    forwardPosition = (currentPiece->getPosition() + diceRoll) % board->getNumberOfFields();
                    if (forwardPosition == 0)
                    {
                        forwardPosition = board->getNumberOfFields();
                    }

                    backwardPosition = (currentPiece->getPosition() - diceRoll);
                    if (backwardPosition <= 0)
                    {
                        backwardPosition = board->getNumberOfFields() + backwardPosition;
                    }

                    // Check these positions for other players
                    IGamePiece_SPTR throwForward = getConflictGamePiece(forwardPosition);
                    IGamePiece_SPTR throwBackward = getConflictGamePiece(backwardPosition);
                    int positionToJumpTo = -1;
                    if ((positionToJumpTo = getJumpPosition(forwardPosition)) > 0 && throwForward == nullptr)
                    {
                        throwForward = getConflictGamePiece(positionToJumpTo);
                        positionToJumpTo = -1;
                    }
                    if ((positionToJumpTo = getJumpPosition(backwardPosition)) > 0 && throwBackward == nullptr)
                    {
                        throwBackward = getConflictGamePiece(positionToJumpTo);
                    }
                    if (throwForward != nullptr)
                    {
                        notOnlyThrowsAllowed = false;
                        // Check if this piece is an own piece. Than others are allowed too if possible.
                        std::vector<IGamePiece_SPTR> ownTeam = board->getTeam(currentPlayer);
                        for (IGamePiece_SPTR &ownPiece : ownTeam)
                        {
                            if (ownPiece->getID() == throwForward->getID())
                            {
                                notOnlyThrowsAllowed = true;
                            }
                        }

                        int jumpPosition;
                        if ((jumpPosition = getJumpPosition(forwardPosition)) != -1)
                        {
                            forwardPosition = jumpPosition;
                        }
                        std::pair<int, bool> position;
                        position.first = forwardPosition;
                        position.second = false;
                        possibilitiesThrow.push_back(position);
                    }
                    if (throwBackward != nullptr)
                    {
                        notOnlyThrowsAllowed = false;
                        // Check if this piece is an own piece. Than others are allowed too if possible.
                        std::vector<IGamePiece_SPTR> ownTeam = board->getTeam(currentPlayer);
                        for (IGamePiece_SPTR &ownPiece : ownTeam)
                        {
                            if (ownPiece->getID() == throwBackward->getID())
                            {
                                notOnlyThrowsAllowed = true;
                            }
                        }

                        int jumpPosition;
                        if ((jumpPosition = getJumpPosition(backwardPosition)) != -1)
                        {
                            backwardPosition = jumpPosition;
                        }
                        std::pair<int, bool> position;
                        position.first = backwardPosition;
                        position.second = false;
                        possibilitiesThrow.push_back(position);
                    }
                }

                // Here old normal stuff
                if (currentPiece->isInTargetArea() && (currentPiece->getPosition() + diceRoll) <= board->getNumberOfGamePiecesPerPlayer() && wayIsFree(currentPiece->getPosition(), currentPiece->getPosition() + diceRoll, currentPlayer))
                {
                    // Check if way is free, if so add
                    printDebug("Is in target area");
                    std::pair<int, bool> position;
                    position.first = currentPiece->getPosition() + diceRoll;

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
                        else
                        {
                            int newPosition = (currentPiece->getPosition() + diceRoll) % board->getNumberOfFields();
                            if (newPosition == 0)
                            {
                                newPosition = board->getNumberOfFields();
                            }
                            int jumpPosition;
                            if ((jumpPosition = getJumpPosition(newPosition)) != -1)
                            {
                                newPosition = jumpPosition;
                            }
                            std::pair<int, bool> position;
                            position.first = newPosition;
                            position.second = false;
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
                        int jumpPosition;
                        if ((jumpPosition = getJumpPosition(newPosition)) != -1)
                        {
                            newPosition = jumpPosition;
                        }
                        std::pair<int, bool> position;
                        position.first = newPosition;
                        position.second = false;
                        possibilities.push_back(position);
                    }
                }
            }
        }
        if (possibilitiesThrow.size() > 0)
        {
            walkAblePiecesThrowing.insert(std::make_pair(currentPiece, possibilitiesThrow));
        }
        if (possibilities.size() > 0)
        {
            printDebug("Add to walkAblePieces");
            walkAblePieces.insert(std::make_pair(currentPiece, possibilities));
        }
    }

    if (notOnlyThrowsAllowed)
    {
        return walkAblePieces;
    }
    else
    {
        return walkAblePiecesThrowing;
    }
}

bool MainLogicHard::pieceOnStartField()
{
    std::vector<IGamePiece_SPTR> team = board->getTeam(currentPlayer);
    for (IGamePiece_SPTR piece : team)
    {
        if (!piece->isInTargetArea() && piece->getPosition() == board->getStartfields()[currentPlayer])
        {
            return true;
        }
    }
    return false;
}

bool MainLogicHard::wayIsFree(int start, int position, int player)
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

bool MainLogicHard::currentPlayerIsAllowedToRollAgain(int currentDiceRoll)
{
    if (currentDiceRoll == 6)
    {
        return false;
    }
    else
    {
        if (board->getOutsideTeam(currentPlayer).size() == 0 && board->getHomeAreaTeam(currentPlayer).size() > 0 && targetTeamFinished(currentPlayer))
        {
            return true;
        }
    }
    return false;
}

bool MainLogicHard::gameIsNotFinished()
{
    bool allPlayerFinished = true;
    for (int player = 0; player < board->getNumberOfPlayers(); player++)
    {
        bool allPiecesFinished = true;
        std::vector<IGamePiece_SPTR> team = board->getTeam(player);
        for (int index = 0; index < team.size(); index++)
        {
            if (!team[index]->isFinished())
            {
                allPiecesFinished = false;
                allPlayerFinished = false;
            }
        }
        if (allPiecesFinished)
        {
            addPlayerToWinnersIfNotPresent(player);
        }
    }
    return !allPlayerFinished;
}

bool MainLogicHard::targetTeamFinished(int currentPlayer)
{
    std::vector<IGamePiece_SPTR> team = board->getTargetAreaTeam(currentPlayer);
    for (int piece = 0; piece < team.size(); piece++)
    {
        if (!team[piece]->isFinished())
        {
            return false;
        }
    }
    return true;
}