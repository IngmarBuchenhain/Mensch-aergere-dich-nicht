#include <iostream>

#include "CppClassMainLogic.hpp"

/** *************************************
 * Constructors of MainLogic            *
 * *************************************/

MainLogic::MainLogic(IUI_SPTR uiObject)
{
    ui = uiObject;
    // Default: So 4 homes, 4 players, 4 pieces per player
    board = std::make_shared<IBoard>();
    // Default: So all rules to false: Default constructor
    rules = std::make_unique<RuleSet>();

    dice = std::make_unique<Dice>();
    currentPlayer = determineStartPlayer(board->getNumberOfPlayers());
}

MainLogic::MainLogic(IUI_SPTR uiObject, int rulesCategory, int numberOfHomes, int numberOfPlayers, int numberOfPieces)
{
    ui = uiObject;
    // Default: So 4 homes, 4 players, 4 pieces per player
    board = std::make_shared<IBoard>();
    // Individual rules
    if(rulesCategory == 0){
        rules = std::make_unique<RuleSet>(); // Default
    }else if(rulesCategory == 1){
        rules = std::make_unique<RuleSet>(false, false, false, true, false, true, false, true, false, false, true, false);
    }else if (rulesCategory == 2){
        rules = std::make_unique<RuleSet>(true, true, true, false, true, false, true, false, true, true ,false, true);
    } else {
        // Exception. Not allowed.
         throw std::invalid_argument("rulesCategory is not in 0..2!");
    }
    

    dice = std::make_unique<Dice>();
    currentPlayer = determineStartPlayer(board->getNumberOfPlayers());
}

/** *************************************
 * Public methods of MainLogic          *
 * *************************************/

void MainLogic::startGame()
{
    // Counter if someone is allowed to roll multiple times (if no piece can walk)
    int rollCounter = 1;

    // GamePiece which was moved in last move
    IGamePiece_SPTR lastGamePiece = nullptr;

    // Game loop. (FUTURE IDEA: Possibility to cancel game)
    while (gameIsNotFinished())
    {
        // Roll dice. Always!
        int currentDiceRoll = dice.roll();

        // Ask current player to roll dice and roll dice (This is not necessary but only for animation or game feeling)
        // TODO Ask player and directly show roll.

        // Indicator whether after this move the next player should be determined or if the current player again
        bool nextPlayer = true;

        // Determine next action:
        if (currentDiceRoll == 6)
        {
            nextPlayer = false;
            // Check if game piece in house
            if (!rules.allowedToUseOutsidePieceOnSixWhenPiecesLeftHome() && currentPlayerHasInHousePieces())
            {
                // Go out
                // RememberFigure
                lastGamePiece = MovePieceToStartField(currentPlayer);
                if (!rules.mustAlwaysFreeStartField() && rules.goWithAnotherPieceOnSecondRollOfDice())
                {
                    // Remember game piece
                    lastGamePiece = nullptr;
                    // Mark as same player
                }
            }
            else
            {
                // Else
                IGamePiece_SPTR pieceToMove;
                // Normal Walk.
                movePiece(pieceToMove, currentDiceRoll);
            }
        }
        else if (currentPlayerIsAllowedToRollAgain())
        {
            // If the current player can not move because all pieces are 'In-House' or in target area (depending on rules how);
            // continue to next roll if not rolled 3 times yet.
            if (rollCounter < 4)
            {
                rollCounter += 1;
                nextPlayer = false;
            }
            else
            {
                // If no roll remaining go to next player
                nextPlayer = true;
            }
        }
        else
        { // Not a 6 and current player can move, so move!

            if (lastGamePiece != nullptr)
            { // Well, we have to go with this game piece, whether we want or not
                // Ask the player out of politness which piece he want to move

                movePiece(lastGamePiece, currentDiceRoll);
            }
            else
            {
                // Determine pieces to move
                std::vector<IGamePieceUI_SPTR> possiblePieces;
                // Ask player which piece to move
                IGamePieceUI_SPTR tempGamePiece = ui->chooseGamePiece(possiblePieces, intToString(currentPlayer));
                IGamePiece_SPTR pieceToMove = dynamic_cast<IGamePiece_SPTR>(tempGamePiece);
                movePiece(pieceToMove, currentDiceRoll);
            }
        }

        // Update UI

        // Determine next current player
        if (nextPlayer)
        {
            rollCounter = 1;
            lastGamePiece = nullptr;
            currentPlayer = determineNextPlayer();
        }
    }

    // Game is finished
    // Present winner on UI
    // Leave game loop (FUTURE IDEA: Possibility for restart?)
}

/** *************************************
 * Private methods of MainLogic         *
 * *************************************/

int MainLogic::determineStartPlayer(int numberOfPlayers){
    return getRandomNumberBetween(0, numberOfPlayers - 1);
}

bool MainLogic::currentPlayerHasInHousePieces()
{
    std::vector<IGamePiece_SPTR> team = board->getTeam(currentPlayer);
    bool hasPiecesInHouse = false;
    for (int piece = 0; piece < team.size(); piece++)
    {
        if (team[piece]->getPosition() == 0)
        {
            hasPiecesInHouse = true;
            break;
        }
    }
    return hasPiecesInHouse;
}
std::string intToString(int number)
{
    if (number == 0)
    {
        return "NULL";
    }
    else if (number == 1)
    {
        return "EINS";
    }
    else if (number == 2)
    {
        return "ZWEI";
    }
    else if (number == 3)
    {
        return "DREI";
    }
}

bool MainLogic::currentPlayerHasOnlyIn()
{
    std::vector<IGamePiece_SPTR> team = board->getTeam(currentPlayer);
    for (int indexOfPiece = 0; indexOfPiece < team.size(); indexOfPiece++)
    {
    }
}

bool MainLogic::currentPlayerIsAllowedToRollAgain()
{
    // Only valid if there are still 'In-House' pieces
    if (currentPlayerHasInHousePieces())
    {
        std::vector<IGamePiece_SPTR> team = board->getTeam(currentPlayer);
        // Check whether all other pieces are in target area and if the rules say so if these cant move anymore
        if (rules.onlyRollThreeTimesIfNoPieceOutAndTargetAreaOnEnd())
        {
            bool allFinished = true;
            for (int indexOfPiece = 0; indexOfPiece < team.size(); indexOfPiece++)
            {
                if (!team[indexOfPiece]->isFinished() && team[indexOfPiece]->getPosition() != 0)
                {
                    allFinished = false;
                }
            }
            return allFinished;
        }
        else
        {
            bool allInTarget = true;
            for (int indexOfPiece = 0; indexOfPiece < team.size(); indexOfPiece++)
            {
                if (!team[indexOfPiece]->isInTargetArea() && team[indexOfPiece]->getPosition() != 0)
                {
                    allInTarget = false;
                }
            }
            return allInTarget;
        }
    }
    return false;
}
std::vector<IGamePiece_SPTR> MainLogic::determineMoveablePieces(int player)
{
    std::vector<IGamePiece_SPTR> currentTeam = gamePieces[player];
    std::vector<IGamePiece_SPTR> possiblePieces;
    for (int pieceIndex = 0; pieceIndex < currentTeam.size(); pieceIndex++)
    {
        if (currentTeam[pieceIndex]->getPosition() != 0)
        {
            if (currentTeam[pieceIndex]->isInTargetArea() && !rules.onlyRollThreeTimesIfNoPieceOutAndTargetAreaOnEnd())
            {
            }
            else if (!currentTeam[pieceIndex]->isInTargetArea())
            {
            }
        }

        if (currentTeam[pieceIndex]->getPosition() != 0 && !((rules.onlyRollThreeTimesIfNoPieceOutAndTargetAreaOnEnd() && isFinished()) || (!rules.onlyRollThreeTimesIfNoPieceOutAndTargetAreaOnEnd() && isInTargetArea())))
        {
            possiblePieces.push_back(currentTeam[pieceIndex]);
        }
    }
    return possiblePieces;
}
IGamePiece_SPTR MainLogic::MovePieceToStartField(int player)
{
    int position = board->startfields[player];
    // Get players team:
    std::vector<IGamePiece_SPTR> team = board->getTeam(player);
    // Piece to move:
    IGamePiece_SPTR movedPiece;
    // Check all pieces of the player until one 'In-House' is found. Move this to the determined start field.
    for (int piece = 0; piece < team.size(); piece++)
    {
        movedPiece = team[piece];
        if (movedPiece->getPosition() == 0)
        {
            movedPiece->setPosition(position);
            // Found one 'In-House' piece. Finish here this loop.
            break;
        }
    }
    // Check for conflicts (only if rules are strict)
    if (!rules.saveOnStartField())
    {
        resolveConflict(movedPiece);
    }
    return movedPiece;
}

IGamePiece_SPTR MainLogic::checkForConflict(IGamePiece_SPTR currentPiece)
{
    // The position to check for other pieces
    int conflictPosition = currentPiece->getPosition();
    // If we are save on the start fields and our position to check is a start field there is no conflict
    if (rules.saveOnStartField() && contains(board->startfields, conflictPosition))
    {
        return nullptr;
    }
    // Check if some other piece, which is not in target area is on this position.
    for (int player = 0; player < board->getNumberOfPlayers(); player++)
    {
        if (player != currentPlayer)
        {
            std::vector<IGamePiece_SPTR> currentTeam = board->getTeam(player);
            for (int inIndex = 0; inIndex < currentTeam.size(); inIndex++)
            {
                if (currentTeam[inIndex]->getPosition() == conflictPosition && !currentTeam[inIndex]->isInTargetArea())
                {
                    currentTeam[inIndex]->setPosition(0);
                }
            }
        }
    }
    if (rules.mustThrowOwnPieces())
    {
        std::vector<IGamePiece_SPTR> currentTeam = board->getTeam(currentPlayer);
        for (int index = 0; index < currentTeam.size(); index++)
        {
            if (currentPiece->getID() != currentTeam[index]->getID() && currentTeam[index]->getPosition() == position)
            {
                currentTeam[index]->setPosition(0);
            }
        }
    }
}
void MainLogic::resolveConflict(IGamePiece_SPTR winner, IGamePiece_SPTR looser)
{
    looser->setPosition(0);
}

IGamePiece_SPTR MainLogic::checkAndResolveConflict(IGamePiece_SPTR currentPiece)
{
    int position = currentPiece->getPosition();
    std::vector<std::vector<IGamePiece_SPTR>> pieces = board->getGamePieces();
    // Check if some other piece, which is not in target area is on this position.
    for (int player = 0; player < board->getNumberOfPlayers(); player++)
    {
        if (player != currentPlayer)
        {
            std::vector<IGamePiece_SPTR> currentTeam = board->getTeam(player);
            for (int inIndex = 0; inIndex < currentTeam.size(); inIndex++)
            {
                if (currentTeam[inIndex]->getPosition() == position && !currentTeam[inIndex]->isInTargetArea())
                {
                    currentTeam[inIndex]->setPosition(0);
                }
            }
        }
    }
    if (rules.mustThrowOwnPieces())
    {
        std::vector<IGamePiece_SPTR> currentTeam = board->getTeam(currentPlayer);
        for (int index = 0; index < currentTeam.size(); index++)
        {
            if (currentPiece->getID() != currentTeam[index]->getID() && currentTeam[index]->getPosition() == position)
            {
                currentTeam[index]->setPosition(0);
            }
        }
    }
}

int MainLogic::determineNextPlayer()
{
    bool searchNextPlayer = true;
    int nextPlayer = currentPlayer;
    while (searchNextPlayer)
    {
        int nextPlayer = (nextPlayer + 1) % board.getNumberOfPlayers();
        if (checkIfPlayerNotFinished(nextPlayer))
        {
            searchNextPlayer = false;
        }
    }
    return nextPlayer;
}

bool MainLogic::checkIfPlayerFinished(int player)
{
    bool result = true;
    for (int index = 0; index < *gamePieces[player].size(); index++)
    {
        if (!*gamePieces[player][index].isFinished())
        {
            result = false;
        }
    }
    return result;
}

bool checkDirectRange(std::vector<int> rangeToCheck)
{
    sort(rangeToCheck.begin(), rangeToCheck.end());
}
void MainLogic::markFinishedPiecesOfTeam(std::vector<IGamePiece_SPTR> &targetAreaPieces)
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
        if(noPieceFound){
            break;
        }
    }
}
bool checkIfFree(std::vector<IGamePiece_SPTR> pieces, int position){
    for(int index = 0; index < pieces.size(); index++){
        if(pieces[index]->getPosition() == position){
            return false;
        }

    }
    return true;
}
bool MainLogic::movePieceToTargetArea(IGamePiece_SPTR piece, int position)
{
    // Get the targetAreaTeam. May be empty
    std::vector<IGamePiece_SPTR> targetTeam = board->getTargetAreaTeam(currentPlayer);

        // Check if move to position possible
        if(rules.jumpOverPiecesInTargetArea()){
            if(checkIfFree(targetTeam, position)){
                piece->setToTargetArea(position);
            }else{
                return false;
            }
        }else{
            bool isFree = true;
            for(int index = piece->isInTargetArea() ? piece->getPosition() + 1 : 1 ; index <= position; index++){
                if(!checkIfFree(targetTeam, position)){
                    isFree = false;
                }
            }
            if(isFree){
                piece->setToTargetArea(position);
            }else{
                return false;
            }
        }

    

    // Check and mark if finished
    
    markFinishedPiecesOfTeam(targetTeam);
    return true;
}
bool contains(std::vector<int> vector, int containedNumber)
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

bool MainLogic::movePiece(IGamePiece_SPTR piece, int numberOfSteps)
{
    // If already in target area
    if (piece->isInTargetArea())
    {
        int newTargetPosition = piece->getPosition() + numberOfSteps;
        movePieceToTargetArea(piece, numberOfSteps);
        return true;
    }
    // Indicator for move into target area
    bool moveIntoTargetArea = false;
    // Indicator for waiting if this is possible by rules
    bool dontWait = true;

    // Get new position
    int walkPosition = piece->getPosition() + numberOfSteps;
    int newPosition = walkPosition % board->getNumberOfFields();

    // Check if 'currentPlayer's endField is between (including) 'piece.getPosition()' and (excluding) 'piece.getPosition() + numberOfSteps'
    // If so, check if possible to go in.
    int endField = board->endFields[currentPlayer];
    if (endField < walkPosition && endField >= piece->getPosition())
    {
        int targetAreaSteps = numberOfSteps - (endField - piece->getPosition());
        if (targetAreaSteps > board->getNumberOfGamePiecesPerPlayer())
        {
            // Not possible to go into target area.
            if (!rules.walkByTargetAreaIfNotPossibleToWalkIn())
            {
                // Wait
                dontWait = false;
            }
        }
        else
        {
            // Check if possible to walk in
            std::vector<IGamePiece_SPTR> team = board->getTeam(currentPlayer);
            std::vector<int> usedTargetFields;
            for (int index = 0; index < team.size(); index++)
            {
                if (team[index]->isInTargetArea())
                {
                    usedTargetFields.push_back(team[index]->getPosition());
                }
            }
            if (rules.jumpOverPiecesInTargetArea())
            {
                // Check if target field is free
                if (!contains(usedTargetFields, targetAreaSteps))
                {
                }
            }
            else
            {
                // Check if all fields until target field are free
                for (int targetField = 1; targetField <= targetAreaSteps; targetField++)
                {
                    if (contains(usedTargetFields, targetField))
                    {
                        // Not possible to walk into target area
                    }
                }
            }
        }
    }
    // Check how many steps are left for target area.
    // check if this is less than all target steps
    // check if no one is in the way (depending on rules);

    // If not possible depending on rules, wait or go on

    if (moveIntoTargetArea)
    {
        movePieceToTargetArea(piece, newPosition);
    }
    else if (dontWait)
    {
        // Set new position to game piece
        piece->setPosition(newPosition);
        resolveConflict(piece);

        // Check if on jumping field. If so jump if rules say so
        int jumpPosition;
        if ((jumpPosition = board->getJumpingField(newPosition)) != -1)
        {
            piece->setPosition(jumpPosition);
            resolveConflict(piece);
        }
    }

    // If moved into target area than nextPlayer = true!
    return moveIntoTargetArea;
}

bool MainLogic::gameIsNotFinished()
{
    // all entries are equal to the wantedNumberInOneEntry
    bool allTeamsFinished = true;
    // one entry is equal to the wantedNumberInOneEntry
    bool oneTeamFinished = false;

    for (int outIndex = 0; outIndex < board.getGamePieces.size(); outIndex++)
    {
        bool allPiecesFinished = true;
        for (int inIndex = 0; inIndex < board.getGamePieces[outIndex].size(); inIndex++)
        {
            if (!board.getGamePieces[outIndex][inIndex].isFinished)
            {
                allPiecesFinished = false;
            }
        }
        if (allPiecesFinished)
        {
            oneTeamFinished = true;
        }
        else
        {
            allTeamsFinished = false;
        }
    }

    return (allTeamsFinished && rules.playUntilAllPlayersFinished) || (!oneTeamFinished && rules.playUntilAllPlayersFinished);

    //     // Check all figures
    // for(int indexOfPiece = 0; indexOfPiece < gamePieces.size(); indexOfPiece++){
    //     if(!gamePieces[indexOfPiece].getPosition().isTargetArea() && rules.playUntilAllPlayersFinished()){
    //         return true;
    //         playersInTargetArea[gamePieces[indexOfPiece].getTeam()] += 1;
    //     } else {

    //     }
    // }
}
