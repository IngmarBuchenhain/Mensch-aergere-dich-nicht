#include "CppClassMainLogicDefault.hpp"
#include<iostream>
#include<string>

/** *************************************
 * Constructors of MainLogic            *
 * *************************************/

MainLogicDefault::MainLogicDefault(IUI_SPTR uiObject)
{
    if (uiObject == nullptr)
    {
        // Exception
    }
    ui = uiObject;
    // Default: So 4 homes, 4 players, 4 pieces per player: Default constructor
    board.reset(new Board());
    // Default: So all rules to false: Default constructor
    rules = std::make_unique<RuleSet>();

    dice = std::make_unique<Dice>();
    currentPlayer = dice->getStartPlayer(board->getNumberOfPlayers());
}

MainLogicDefault::MainLogicDefault(IUI_SPTR uiObject, int numberOfHomes, int numberOfPlayers, int numberOfPieces)
{
    ui = uiObject;
    // Default: So 4 homes, 4 players, 4 pieces per player
    IBoard_SPTR tempBoard(new Board());
    board = tempBoard;
    // Individual rules

        rules = std::make_unique<RuleSet>(); // Default
  

    dice = std::make_unique<Dice>();
    currentPlayer = dice->getStartPlayer(board->getNumberOfPlayers());
}

/** *************************************
 * Public methods of MainLogic          *
 * *************************************/

void MainLogicDefault::startGame()
{
    printDebug("Started game");
    ui->initBoard(board);
    // Counter if someone is allowed to roll multiple times (if no piece can walk)
    int rollCounter = 1;

    // GamePiece which was moved in last move
    IGamePiece_SPTR lastGamePiece = nullptr;

    // Game loop. (FUTURE IDEA: Possibility to cancel game)
    while (gameIsNotFinished())
    {
        printDebug("Loop running..");
        printDebug("Current player: ");
        printDebug(currentPlayer);

        // Roll dice. Always!
        int currentDiceRoll = dice->roll();
        printDebug(currentDiceRoll);
        // Ask current player to roll dice and roll dice (This is not necessary but only for animation or game feeling)
        // TODO Ask player and directly show roll.

        ui->rollDice(currentPlayer, currentDiceRoll);

        // Indicator whether after this move the next player should be determined or if the current player again
        bool nextPlayer = true;

        // Determine next action:
if (currentPlayerIsAllowedToRollAgain(currentDiceRoll))
        { 
            printDebug("No 6; 3 Times");
            // If the current player can not move because all pieces are 'In-House' or in target area (depending on rules how);
            // continue to next roll if not rolled 3 times yet.
            if (rollCounter < 3)
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
else{
        // Determine all possible walking moves
//printDebug("Get pieces selection");

std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> moveAblePieces = getGamePiecesWithNewPositions(currentDiceRoll, lastGamePiece);
//printDebug("Selection found");
        // Get Selection from UI
        std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> selectable = convertMapForUI(moveAblePieces);
        //printDebug("Converted");
        if(selectable.size() == 0){
            printDebug("No pieces possible");
        }else{
            printDebug("Pieces possible");
        std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> selection = ui->chooseOneGamePiece(selectable);
        printDebug("chosen");
        printDebug(selection.first->getID());
        // If we had a 6 mark it
        if(currentDiceRoll == 6 && !selection.second.second){
            printDebug("Mark last piece");
            lastGamePiece = std::dynamic_pointer_cast<IGamePiece>(selection.first);
            if(lastGamePiece == nullptr){
                printDebug("Bad");
            }
            nextPlayer = false;
        }
        std::pair<IGamePiece_SPTR, std::pair<int, bool>> convertedSelection;
        convertedSelection.first = std::dynamic_pointer_cast<IGamePiece> (selection.first);
        convertedSelection.second = selection.second;

        // Move
        printDebug("Now moving piece");
        if(convertedSelection.second.second){
            printDebug("Target Area");
            movePieceInTargetArea(convertedSelection.first, convertedSelection.second.first);
        } else {
            printDebug("Field");
            movePieceOnField(convertedSelection.first, convertedSelection.second.first);
        }
        }



}
        // Update UI
        std::vector<std::vector<IGamePieceUI_SPTR>> pieces = board->getGamePieces();
        //std::cout << std::endl << pieces.size() << std::endl << std::flush;
            ui->updateBoard(pieces);
        // Determine next current player
        if (nextPlayer)
        {
            //printDebug("Determine next player");
            rollCounter = 1;
            lastGamePiece = nullptr;
            currentPlayer = determineNextPlayer();
        }
    }

    // Game is finished
    printDebug("Game finished");
    // Present winner on UI
    ui->showInformation("The winner is:");
    ui->showInformation(std::to_string(winners[0]));
    printDebug("The winners are: ");
    printDebug(winners);

    // Leave game loop (FUTURE IDEA: Possibility for restart?)
    printDebug("End of game");
}

/** *************************************
 * Private methods of MainLogic         *
 * *************************************/

// // Checked
// void MainLogic::movePieceOnField(IGamePiece_SPTR piece, int position)
// {
//     // Argument checks
//     if (piece->isInTargetArea())
//     {
//         throw new unexpected_game_piece;
//     }
//     if (position < 1 || position > board->getNumberOfFields())
//     {
//         throw new illegal_position;
//     }

//     // Check if position is already used and resolve conflict
//     IGamePiece_SPTR conflictGamePiece = getConflictGamePiece(position);
//     if(conflictGamePiece != nullptr){
//     conflictGamePiece->setPosition(0);
//     }


//     // Set new position
//     piece->setPosition(position);
// }

// // Checked
// void MainLogic::movePieceInTargetArea(IGamePiece_SPTR piece, int position)
// {
//     // Argument checks
//     if (piece->isFinished())
//     {
//         throw new unexpected_game_piece;
//     }
//     if (position < 1 || position > board->getNumberOfGamePiecesPerPlayer())
//     {
//         throw new illegal_position;
//     }

//     // Set new position. No conflict check needed in target area!
//     piece->setToTargetArea(position);

//     // Check if piece/pieces of player is/are finished
//     std::vector<IGamePiece_SPTR> team = board->getTargetAreaTeam(currentPlayer);
//     markFinishedPiecesOfTeam(team);
// }

// // Checked
// IGamePiece_SPTR MainLogic::getConflictGamePiece(int position){
//         // If we are save on the start fields and our position to check is a start field there is no conflict
//     if (rules->saveOnStartField() && contains(board->getStartfields(), position))
//     {
//         return nullptr;
//     }
//     // Check if some other piece, which is not in target area is on this position.
//     for (int player = 0; player < board->getNumberOfPlayers(); player++)
//     {
//         std::vector<IGamePiece_SPTR> currentTeam = board->getOutsideTeam(player);
//         if (player != currentPlayer || rules->mustThrowOwnPieces())
//         {
            
//             for (int inIndex = 0; inIndex < currentTeam.size(); inIndex++)
//             {
//                 if (currentTeam[inIndex]->getPosition() == position)
//                 {
//                     return currentTeam[inIndex];
                 
//                 }
//             }
//         }
//     }
// }


std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> MainLogicDefault::getGamePiecesWithNewPositions(int diceRoll, IGamePiece_SPTR lastPiece){
    std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> walkAblePieces;
    std::vector<IGamePiece_SPTR> team = board->getTeam(currentPlayer);
    bool alreadyFinished = false;
    for(int pieceIndex = 0; pieceIndex < team.size(); pieceIndex++){
       // printDebug("Current piece ID to check possibilites");
        
        IGamePiece_SPTR currentPiece = team[pieceIndex];
       // printDebug(currentPiece->getID());
       // printDebug(currentPiece->getPosition());
        if(alreadyFinished){
            break;
        }
        if(lastPiece != nullptr){ 
            printDebug("Take same piece");

            currentPiece = lastPiece;
            alreadyFinished = true;
        }
        std::vector<std::pair<int, bool>> possibilities;
        if(diceRoll == 6 && currentPiece->getPosition() == 0)
        { // 6 Check

 
                    // Get startfield
                    int start = board->getStartfields()[currentPlayer];
                    std::pair<int, bool> position;
                    position.first = start;
                    position.second = false;
                    possibilities.push_back(position);
        

                
            
        } else {
            // No 6 or not an
            // Get possibilities
            bool getPossibilities = true;
                                if(diceRoll == 6 && board->getHomeAreaTeam(currentPlayer).size() != 0){
                        
                        getPossibilities = false;
                        
                    }
                    if(getPossibilities){
                        if(currentPiece->isInTargetArea() && (currentPiece->getPosition() + diceRoll) <= board->getNumberOfGamePiecesPerPlayer() && wayIsFree(currentPiece->getPosition(), currentPiece->getPosition() + diceRoll, currentPlayer)){
                            // Check if way is free, if so add
                            printDebug("Is in target area");
                            std::pair<int, bool> position;
                            position.first = currentPiece->getPosition() + diceRoll;
                            printDebug(currentPiece->getPosition() + diceRoll);
                            position.second = true;
                            possibilities.push_back(position);
                        } else if(!currentPiece->isInTargetArea() && currentPiece->getPosition() != 0) {

                            // Check if endField is in range
                            int targetAreaPosition;
                            if((targetAreaPosition = containsEndField(currentPiece->getPosition(), diceRoll, currentPlayer)) != -1){
                                printDebug("Going to target area - Number:");
                                printDebug(targetAreaPosition);
                                if(wayIsFree(0, targetAreaPosition, currentPlayer)){
                                    std::pair<int, bool> position;
                                    position.first = targetAreaPosition;
                                    position.second = true;
                                    possibilities.push_back(position);
                                }
                            } else {
                                                        // Get new position
                                                        printDebug("Normal walk");
                            int newPosition = (currentPiece->getPosition() + diceRoll) % board->getNumberOfFields();
                            if(newPosition == 0){
                                newPosition = board->getNumberOfFields();
                            }

                            printDebug(newPosition);
                            if(noOwnPieceThere(newPosition)){
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
        }
        if(possibilities.size() > 0){
            printDebug("Add to walkAblePieces");
            walkAblePieces.insert(std::make_pair(currentPiece, possibilities));
        }
    }

    return walkAblePieces;
}

bool MainLogicDefault::noOwnPieceThere(int newPosition){
    std::vector<IGamePiece_SPTR> team = board->getTeam(currentPlayer);
    for(int index = 0; index < team.size(); index++){
        if(team[index]->getPosition() == newPosition){
            return false;
        }
    }
    return true;
}

bool MainLogicDefault::positionIsFree(int field, int player){
    std::vector<IGamePiece_SPTR> team = board->getTeam(player);
    for(int index = 0; index < team.size(); index++){
        if(team[index]->getPosition() == field){
            return false;
        }
    }
    return true;
}

bool MainLogicDefault::wayIsFree(int start, int position, int player){
    std::vector<IGamePiece_SPTR> team = board->getTeam(player);
    for(int index = 0; index < team.size(); index++){
        for(int posIndex = start + 1; posIndex <= position; posIndex++){
            if(!positionIsFree(posIndex, player)){
                return false;
            }
        }
    }
return true;
}

std::vector<std::pair<int, bool>> getPotentialNewPositions(int currentPosition, int numberOfSteps, int numberOfFields, int startField, bool isAlreadyInTarget){
    std::vector<std::pair<int, bool>> result;
    if(currentPosition == 0){
          std::pair<int, bool> pair;
          pair.first = startField;
          pair.second = false;
          result.push_back(pair);
          return result;
    }
    if(isAlreadyInTarget){

    }   
     int newPositionPositive = (currentPosition + numberOfSteps) % numberOfFields;
    if(newPositionPositive == 0){
        newPositionPositive = numberOfFields;
    }
    int newPositionNegative = (currentPosition - numberOfSteps) % numberOfFields;
}

bool test(int currentPosition, int numberOfSteps, int startField, int endField, int numberOfFields){

}



// bool MainLogic::currentPlayerHasInHousePieces()
// {
//     std::vector<IGamePiece_SPTR> team = board->getTeam(currentPlayer);
//     bool hasPiecesInHouse = false;
//     for (int piece = 0; piece < team.size(); piece++)
//     {
//         if (team[piece]->getPosition() == 0)
//         {
//             hasPiecesInHouse = true;
//             break;
//         }
//     }
//     return hasPiecesInHouse;
// }

bool MainLogicDefault::currentPlayerIsAllowedToRollAgain(int currentDiceRoll)
{
    if(currentDiceRoll == 6){
        return false;
    } else{
        if(board->getOutsideTeam(currentPlayer).size() == 0 && board->getHomeAreaTeam(currentPlayer).size() > 0){
            return true;
        }
    }
    
}

// bool MainLogicDefault::currentPlayerIsAllowedToRollAgain()
// {
//     // Only valid if there are still 'In-House' pieces
//     if (currentPlayerHasInHousePieces())
//     {
//         std::vector<IGamePiece_SPTR> team = board->getTeam(currentPlayer);
//         // Check whether all other pieces are in target area and if the rules say so if these cant move anymore
//         if (rules->onlyRollThreeTimesIfNoPieceOutAndTargetAreaOnEnd())
//         {
//             bool allFinished = true;
//             for (int indexOfPiece = 0; indexOfPiece < team.size(); indexOfPiece++)
//             {
//                 if (!team[indexOfPiece]->isFinished() && team[indexOfPiece]->getPosition() != 0)
//                 {
//                     allFinished = false;
//                 }
//             }
//             return allFinished;
//         }
//         else
//         {
//             bool allInTarget = true;
//             for (int indexOfPiece = 0; indexOfPiece < team.size(); indexOfPiece++)
//             {
//                 if (!team[indexOfPiece]->isInTargetArea() && team[indexOfPiece]->getPosition() != 0)
//                 {
//                     allInTarget = false;
//                 }
//             }
//             return allInTarget;
//         }
//     }
//     return false;
// }


std::vector<IGamePiece_SPTR> MainLogicDefault::determinePossiblePieces(std::vector<IGamePiece_SPTR> &moveablePieces, int numberOfSteps)
{
    std::vector<IGamePiece_SPTR> result;
    std::vector<IGamePiece_SPTR> team = board->getTargetAreaTeam(currentPlayer);

    for (int index = 0; index < moveablePieces.size(); index++)
    {
        IGamePiece_SPTR currentPiece = moveablePieces[index];
        if (currentPiece->isInTargetArea())
        {
            // Check if able to walk
            int targetAreaPosition = currentPiece->getPosition() + numberOfSteps;
            if (targetAreaPosition <= board->getNumberOfGamePiecesPerPlayer())
            {
                // Theoretical able to walk
                // Check if possible
                for (int targetIndex = 0; targetIndex < team.size(); targetIndex++)
                {
                    if (targetAreaPosition == team[targetIndex]->getPosition())
                    {
                    }
                }
            }
        }
        else
        {
        }
    }

    return result;
}

std::vector<IGamePiece_SPTR> MainLogicDefault::determineMoveablePieces(int player)
{
    // Get current team and init selection of moveable pieces
    std::vector<IGamePiece_SPTR> currentTeam = board->getTeam(player);
    std::vector<IGamePiece_SPTR> possiblePieces;
    // Check whole team of applicable
    for (int pieceIndex = 0; pieceIndex < currentTeam.size(); pieceIndex++)
    {
        // Only if not 'In-House' possibly moveable
        if (currentTeam[pieceIndex]->getPosition() != 0)
        {
            if (!currentTeam[pieceIndex]->isInTargetArea())
            {
                possiblePieces.push_back(currentTeam[pieceIndex]);
            }
            else
            {
                if (!currentTeam[pieceIndex]->isFinished())
                {
                    possiblePieces.push_back(currentTeam[pieceIndex]);
                }
            }
        }
    }
    return possiblePieces;
}

// bool contains(std::vector<int> vector, int containedNumber)
// {
//     bool isContained = false;
//     for (int index = 0; index < vector.size(); index++)
//     {
//         if (vector[index] == containedNumber)
//         {
//             isContained = true;
//         }
//     }
//     return isContained;
// }

IGamePiece_SPTR MainLogicDefault::MovePieceToStartField(int player)
{
    int position = board->getStartfields()[player];
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
    if (!rules->saveOnStartField())
    {
        //resolveConflict(movedPiece);
    }
    return movedPiece;
}

IGamePiece_SPTR MainLogicDefault::checkForConflict(IGamePiece_SPTR currentPiece)
{
    // The position to check for other pieces
    int conflictPosition = currentPiece->getPosition();
    // If we are save on the start fields and our position to check is a start field there is no conflict
    if (rules->saveOnStartField() && contains(board->getStartfields(), conflictPosition))
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
    if (rules->mustThrowOwnPieces())
    {
        std::vector<IGamePiece_SPTR> currentTeam = board->getTeam(currentPlayer);
        for (int index = 0; index < currentTeam.size(); index++)
        {
            if (currentPiece->getID() != currentTeam[index]->getID() && currentTeam[index]->getPosition() == conflictPosition)
            {
                currentTeam[index]->setPosition(0);
            }
        }
    }
}
void MainLogicDefault::resolveConflict(IGamePiece_SPTR winner, IGamePiece_SPTR looser)
{
    looser->setPosition(0);
}

// IGamePiece_SPTR MainLogic::checkAndResolveConflict(IGamePiece_SPTR currentPiece)
// {
//     int position = currentPiece->getPosition();
//     std::vector<std::vector<IGamePiece_SPTR>> pieces = board->getGamePieces();
//     // Check if some other piece, which is not in target area is on this position.
//     for (int player = 0; player < board->getNumberOfPlayers(); player++)
//     {
//         if (player != currentPlayer)
//         {
//             std::vector<IGamePiece_SPTR> currentTeam = board->getTeam(player);
//             for (int inIndex = 0; inIndex < currentTeam.size(); inIndex++)
//             {
//                 if (currentTeam[inIndex]->getPosition() == position && !currentTeam[inIndex]->isInTargetArea())
//                 {
//                     currentTeam[inIndex]->setPosition(0);
//                 }
//             }
//         }
//     }
//     if (rules->mustThrowOwnPieces())
//     {
//         std::vector<IGamePiece_SPTR> currentTeam = board->getTeam(currentPlayer);
//         for (int index = 0; index < currentTeam.size(); index++)
//         {
//             if (currentPiece->getID() != currentTeam[index]->getID() && currentTeam[index]->getPosition() == position)
//             {
//                 currentTeam[index]->setPosition(0);
//             }
//         }
//     }
// }

// int MainLogic::determineNextPlayer()
// {
//     bool searchNextPlayer = true;
//     int nextPlayer = currentPlayer;
//     printDebug(nextPlayer);
//     while (searchNextPlayer)
//     {
//         nextPlayer = (nextPlayer + 1) % board->getNumberOfPlayers();
//         if (playerIsNotFinished(nextPlayer))
//         {
//             printDebug("Next player found");

//             searchNextPlayer = false;
//         }
//     }
//     printDebug(nextPlayer);
//     return nextPlayer;
// }

// bool MainLogic::playerIsNotFinished(int player)
// {
//     bool result = false;
//     for (int index = 0; index < board->getTeam(player).size(); index++)
//     {
//         if (!board->getTeam(player)[index]->isFinished())
//         {
//             result = true;
//         }
//     }

//     return result;
// }

// bool checkDirectRange(std::vector<int> rangeToCheck)
// {
//     sort(rangeToCheck.begin(), rangeToCheck.end());
// }
// void MainLogic::markFinishedPiecesOfTeam(std::vector<IGamePiece_SPTR> &targetAreaPieces)
// {
//     // Check all target area position. Start with the hightest, because only then a game piece can be finished when no free position before are left.
//     for (int position = board->getNumberOfGamePiecesPerPlayer(); position > 0; position--)
//     {
//         // Check all target area pieces if they are on the current position. If not no other piece can be finished. So skip remaining.
//         bool noPieceFound = true;
//         for (int piece = 0; piece < targetAreaPieces.size(); piece++)
//         {
//             if (targetAreaPieces[piece]->getPosition() == position)
//             {
//                 targetAreaPieces[piece]->setFinished();
//                 noPieceFound = false;
//             }
//         }
//         if (noPieceFound)
//         {
//             break;
//         }
//     }
// }
// bool checkIfFree(std::vector<IGamePiece_SPTR> pieces, int position)
// {
//     for (int index = 0; index < pieces.size(); index++)
//     {
//         if (pieces[index]->getPosition() == position)
//         {
//             return false;
//         }
//     }
//     return true;
// }
bool MainLogicDefault::movePieceToTargetArea(IGamePiece_SPTR piece, int position)
{
    // Get the targetAreaTeam. May be empty
    std::vector<IGamePiece_SPTR> targetTeam = board->getTargetAreaTeam(currentPlayer);

    // Check if move to position possible
    if (rules->jumpOverPiecesInTargetArea())
    {
        if (checkIfFree(targetTeam, position))
        {
            piece->setToTargetArea(position);
        }
        else
        {
            return false;
        }
    }
    else
    {
        bool isFree = true;
        for (int index = piece->isInTargetArea() ? piece->getPosition() + 1 : 1; index <= position; index++)
        {
            if (!checkIfFree(targetTeam, position))
            {
                isFree = false;
            }
        }
        if (isFree)
        {
            piece->setToTargetArea(position);
        }
        else
        {
            return false;
        }
    }

    // Check and mark if finished

    markFinishedPiecesOfTeam(targetTeam);
    return true;
}

bool MainLogicDefault::movePiece(IGamePiece_SPTR piece, int numberOfSteps)
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
    int endField = board->getEndFields()[currentPlayer];
    if (endField < walkPosition && endField >= piece->getPosition())
    {
        int targetAreaSteps = numberOfSteps - (endField - piece->getPosition());
        if (targetAreaSteps > board->getNumberOfGamePiecesPerPlayer())
        {
            // Not possible to go into target area.
            if (!rules->walkByTargetAreaIfNotPossibleToWalkIn())
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
            if (rules->jumpOverPiecesInTargetArea())
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
        //resolveConflict(piece);

        // Check if on jumping field. If so jump if rules say so
        int jumpPosition;
        if ((jumpPosition = getJumpPosition(newPosition)) != -1)
        {
            piece->setPosition(jumpPosition);
            //resolveConflict(piece);
        }
    }

    // If moved into target area than nextPlayer = true!
    return moveIntoTargetArea;
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
