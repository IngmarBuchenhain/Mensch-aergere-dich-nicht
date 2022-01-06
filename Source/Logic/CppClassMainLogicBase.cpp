#include "CppClassMainLogicBase.hpp"
#include "CppDebugHelper.hpp"

/** ***************************************
 * Protected methods of MainLogicBase     *
 * ***************************************/

int MainLogicBase::determineNextPlayer()
{
    bool searchNextPlayer = true;
    int nextPlayer = currentPlayer;
    printDebug("CurrentPlayer: " + std::to_string(nextPlayer));

    // Search so long for next player until one is found which has not finished yet or until all were tested. If so the game is finished anyways.
    for (int testedPlayers = 0; testedPlayers < board->getNumberOfPlayers(); testedPlayers++)
    {
        nextPlayer = (nextPlayer + 1) % board->getNumberOfPlayers();
        if (playerIsNotFinished(nextPlayer))
        {
            printDebug("Next player found: " + std::to_string(nextPlayer));
            break;
        }
    }
    return nextPlayer;
}

bool MainLogicBase::playerIsNotFinished(int player)
{
    bool result = false;
    for (int index = 0; index < board->getTeam(player).size(); index++)
    {
        if (!board->getTeam(player)[index]->isFinished())
        {
            result = true;
        }
    }
    return result;
}

void MainLogicBase::addPlayerToWinnersIfNotPresent(int player)
{
    // Check if already present
    bool alreadyPresent = false;
    for (int index = 0; index < winners.size(); index++)
    {
        if (winners[index] == player)
        {
            alreadyPresent = true;
        }
    }
    if (!alreadyPresent)
    {
        winners.push_back(player);
    }
}

int MainLogicBase::getJumpPosition(int field)
{
    std::vector<IJumpPair_SPTR> jumps = board->getJumpFields();
    for (int index = 0; index < jumps.size(); index++)
    {
        int result;
        if ((result = jumps[index]->getPartnerOrNegative(field)) != -1)
        {
            return result;
        }
    }
    return -1;
}

bool MainLogicBase::checkIfFree(std::vector<IGamePiece_SPTR> pieces, int position)
{
    for (int index = 0; index < pieces.size(); index++)
    {
        if (pieces[index]->getPosition() == position)
        {
            return false;
        }
    }
    return true;
}

void MainLogicBase::markFinishedPiecesOfTeam(std::vector<IGamePiece_SPTR> &targetAreaPieces)
{
    // Check all target area position. Start with the hightest, because only then a game piece can be finished when no free position before are left.
    for (int position = board->getNumberOfGamePiecesPerPlayer(); position > 0; position--)
    {
        // Check all target area pieces if they are on the current position. If not no other piece can be finished. So skip remaining.
        bool noPieceFound = true;
        for (int piece = 0; piece < targetAreaPieces.size(); piece++)
        {
            if (targetAreaPieces[piece]->getPosition() == position)
            {
                targetAreaPieces[piece]->setFinished();
                noPieceFound = false;
            }
        }
        if (noPieceFound)
        {
            break;
        }
    }
}

bool MainLogicBase::contains(std::vector<int> vector, int containedNumber)
{
    bool isContained = false;
    for (int index = 0; index < vector.size(); index++)
    {
        if (vector[index] == containedNumber)
        {
            isContained = true;
        }
    }
    return isContained;
}

int MainLogicBase::containsEndField(int start, int steps, int player)
{
    int targetPosition;
    printDebug("Searching endField contained - endField is: " + std::to_string(board->getEndFields()[player]));

    for (int currentField = start; currentField < start + steps; currentField++)
    {
        printDebug("Current field which is checked: " + currentField);
        if (currentField == board->getEndFields()[player])
        {
            // Get new position
            targetPosition = (start + steps) - currentField;
            if (targetPosition <= board->getNumberOfGamePiecesPerPlayer())
            {
                printDebug("endField is contained. Return new position in target area");
                return targetPosition;
            }
        }
    }
    return -1;
}

std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> MainLogicBase::convertMapForUI(std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> &origin)
{
    std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> result;
    std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>>::iterator it = origin.begin();
    while (it != origin.end())
    {
        IGamePieceUI_SPTR convertedPiece = it->first;
        result[convertedPiece] = it->second;
        it++;
    }
    return result;
}

void MainLogicBase::movePieceOnField(IGamePiece_SPTR piece, int position)
{
    // Argument checks
    if (piece->isInTargetArea())
    {
        printDebug("Unexpected GamePiece in MoveOnField");
        throw new unexpected_game_piece;
    }
    if (position < 1 || position > board->getNumberOfFields())
    {
        printDebug("Illegal position in MoveOnField");
        throw new illegal_position;
    }
    printDebug("Search conflicts");
    // Check if position is already used and resolve conflict
    IGamePiece_SPTR conflictGamePiece = getConflictGamePiece(position);

    if (conflictGamePiece != nullptr)
    {
        printDebug("Got conflict pieces");
        conflictGamePiece->setPosition(0);
    }

    // Set new position
    piece->setPosition(position);
}

void MainLogicBase::movePieceInTargetArea(IGamePiece_SPTR piece, int position)
{
    // Argument checks
    if (piece->isFinished())
    {
        printDebug("Unexpected GamePiece in MoveInTargetArea");
        throw new unexpected_game_piece;
    }
    if (position < 1 || position > board->getNumberOfGamePiecesPerPlayer())
    {
        printDebug("Illegal position in MoveInTargetArea");
        throw new illegal_position;
    }

    // Set new position. No conflict check needed in target area!
    piece->setToTargetArea(position);

    // Check if piece/pieces of player is/are finished
    std::vector<IGamePiece_SPTR> team = board->getTargetAreaTeam(currentPlayer);
    markFinishedPiecesOfTeam(team);
}

IGamePiece_SPTR MainLogicBase::getConflictGamePiece(int position)
{
    // If we are save on the start fields and our position to check is a start field there is no conflict
    if (rules->saveOnStartField() && contains(board->getStartfields(), position))
    {
        printDebug("Return nullptr as there is no conflict");
        return nullptr;
    }

    // Check if some other piece, which is not in target area is on this position.
    for (int player = 0; player < board->getNumberOfPlayers(); player++)
    {
        printDebug("In search-loop for other pieces");
        std::vector<IGamePiece_SPTR> currentTeam = board->getOutsideTeam(player);
        if (player != currentPlayer || rules->mustThrowOwnPieces())
        {

            for (int inIndex = 0; inIndex < currentTeam.size(); inIndex++)
            {
                if (currentTeam[inIndex]->getPosition() == position)
                {
                    return currentTeam[inIndex];
                }
            }
        }
    }
    // No conflicting piece found
    return nullptr;
}

bool MainLogicBase::positionInTargetAreaIsFree(int field, int player){
    std::vector<IGamePiece_SPTR> team = board->getTeam(player);
    for(int index = 0; index < team.size(); index++){
        if(team[index]->getPosition() == field){
            return false;
        }
    }
    return true;
}

bool MainLogicBase::noOwnPieceThere(int newPosition){
    std::vector<IGamePiece_SPTR> team = board->getTeam(currentPlayer);
    for(int index = 0; index < team.size(); index++){
        if(team[index]->getPosition() == newPosition){
            return false;
        }
    }
    return true;
}