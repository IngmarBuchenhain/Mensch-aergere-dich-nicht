#include "CppClassMainLogicBase.hpp"
#include "CppDebugHelper.hpp"
#include "CppClassKI.hpp"

/** ***************************************
 * Constructors of MainLogicBase          *
 * ***************************************/

MainLogicBase::MainLogicBase(IUI_SPTR uiObject)
{
    if (uiObject == nullptr)
    {
        throw argument_nullptr_exception();
    }
    ui = uiObject;

    // Default: So 4 homes, 4 players, 4 pieces per player: Default constructor
    board.reset(new Board());

    // Default: So all rules to false: Default constructor
    //rules = std::make_unique<RuleSet>();

    // Init dice
    dice = std::make_unique<Dice>();

    // Roll the start player
    currentPlayer = dice->getStartPlayer(board->getNumberOfPlayers());

    // Init stats object
    stats = std::make_unique<Statistics>();

    // Init KI.
    int countHuman = 1;
    for (int index = 0; index < board->getNumberOfHomes(); index++)
    {
        kiPlayer[index] = nullptr;
        std::string name = "StealthPlayer ";
        name.append(std::to_string(countHuman));

        nameOfPlayers.push_back(name);
        countHuman += 1;
        //kiPlayer[index] = std::make_unique<KI>(board->getEndFields()[index], board->getNumberOfFields()); // for Debug
    }
}

MainLogicBase::MainLogicBase(IUI_SPTR uiObject, int numberOfHomes, int numberOfPlayers, int numberOfPieces, bool fillWithKI, bool spreadOnBoard, std::vector<std::string> playerNames)
{
    if (uiObject == nullptr)
    {
        throw argument_nullptr_exception();
    }
    ui = uiObject;

    if (numberOfPlayers < 1 || numberOfPlayers > 6 || (numberOfHomes != 4 && numberOfHomes != 6) || numberOfHomes < numberOfPlayers || (numberOfPieces != 3 && numberOfPieces != 4))
    {
        throw illegal_argument();
    }

    // Default: So 4 homes, 4 players, 4 pieces per player

    // Check if there are less players than homes. If so, check if, filled with KI is true. If not, check if spreadOnBoard is true
    int numberOfAllPlayers = numberOfPlayers;
    for (int index = 0; index < numberOfPlayers; index++)
    {

        kiPlayer[index] = nullptr;
    }
    if (numberOfPlayers < numberOfHomes)
    {
        if (fillWithKI)
        {
            // Note which are KI and which not

            // Set numberOfPlayers to numberOfHomes
            numberOfAllPlayers = numberOfHomes;

            // Mark which ones are KI and mark names right
        }
    }

    board.reset(new Board(numberOfHomes == 4 ? false : true, numberOfAllPlayers, numberOfPieces, spreadOnBoard));
    // Individual rules

    

    dice = std::make_unique<Dice>();
    currentPlayer = dice->getStartPlayer(board->getNumberOfPlayers());
    stats = std::make_unique<Statistics>();
    if (fillWithKI)
    {
        for (int index = numberOfPlayers; index < numberOfHomes; index++)
        {
            kiPlayer[index] = std::make_unique<KI>(board->getEndFields()[index], board->getNumberOfFields());
        }
    }
    if (playerNames.size() < numberOfAllPlayers)
    {
        int countKI = 1;
        int countHuman = 1;
        for (int index = playerNames.size(); index < numberOfAllPlayers; index++)
        {
            if (kiPlayer[index] != nullptr)
            {
                std::string name = "ThenotsointelligentbutluckyKI ";
                name.append(std::to_string(countKI));
                playerNames.push_back(name);
                countKI += 1;
            }
            else
            {
         
                std::string name = "StealthPlayer ";
                name.append(std::to_string(countHuman));
  
                playerNames.push_back(name);
                countHuman += 1;
            }
        }
    }
    nameOfPlayers = playerNames;
}
/** ***************************************
 * Public methods of MainLogicBase        *
 * ***************************************/


void MainLogicBase::startGame()
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
        stats->addDiceRoll(currentDiceRoll);
        printDebug(currentDiceRoll);
        // Ask current player to roll dice and roll dice (This is not necessary but only for animation or game feeling)
        // TODO Ask player and directly show roll.
        // if KI present choice, other ask
        if(kiPlayer[currentPlayer] == nullptr){
 ui->rollDice(nameOfPlayers[currentPlayer], currentDiceRoll);
        } else{
            ui->showInformation(nameOfPlayers[currentPlayer] + " rolled a -" + std::to_string(currentDiceRoll) + "-");
        }
       

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
        else
        {
            // Determine all possible walking moves
            //printDebug("Get pieces selection");

            std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> moveAblePieces = getGamePiecesWithNewPositions(currentDiceRoll, lastGamePiece);
            //printDebug("Selection found");
            // Get Selection from UI
            std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> selectable = convertMapForUI(moveAblePieces);
            //printDebug("Converted");
            if (selectable.size() == 0)
            {
                printDebug("No pieces possible");
            }
            else
            {
                printDebug("Pieces possible");
                std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> selection;
                // Let user or KI choose:
                if (kiPlayer[currentPlayer] != nullptr)
                {
                    printDebug("KI");
                    selection = kiPlayer[currentPlayer]->chooseGamePiece(selectable);
                    ui->showInformation(nameOfPlayers[currentPlayer] + " chose a game piece");
                }
                else
                {
                    selection = ui->chooseOneGamePiece(selectable, nameOfPlayers[currentPlayer]);
                }

                printDebug("chosen");
                printDebug(selection.first->getID());
                // If we had a 6 mark it
                if (currentDiceRoll == 6 && !selection.second.second)
                {
                    printDebug("Mark last piece");
                    if(!rules->goWithAnotherPieceOnSecondRollOfDice()){
 lastGamePiece = std::dynamic_pointer_cast<IGamePiece>(selection.first);
                    }
                   

                    nextPlayer = false;
                }
                std::pair<IGamePiece_SPTR, std::pair<int, bool>> convertedSelection;
                convertedSelection.first = std::dynamic_pointer_cast<IGamePiece>(selection.first);
                convertedSelection.second = selection.second;

                // Move
                printDebug("Now moving piece");
                if (convertedSelection.second.second)
                {
                    printDebug("Target Area");
                    movePieceInTargetArea(convertedSelection.first, convertedSelection.second.first);
                }
                else
                {
                    printDebug("Field");
                    movePieceOnField(convertedSelection.first, convertedSelection.second.first);
                    if(rules->jumpOnEdges()){
                        // Check if we are on jump field. If so, we have to check the position we jumped from to.
                        int positionWeJumpedFrom = getJumpPosition(convertedSelection.second.first);
                        IGamePiece_SPTR conflictPiece = nullptr;
                        do
                        {
                                          if((conflictPiece = getConflictGamePiece(positionWeJumpedFrom)) != nullptr){
                                              conflictPiece->setPosition(0);
                                             
                        }
                        } while (conflictPiece != nullptr);
                        

                    }
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
    ui->showInformation("The winner is: " + std::to_string(winners[0]));
    //ui->showInformation(std::to_string(winners[0]));
    printDebug("The winners are: ");
    printDebug(winners);
    stats->showDiceStats();

    // Leave game loop (FUTURE IDEA: Possibility for restart?)
    printDebug("End of game");
}

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
    std::vector<IGamePiece_SPTR> team = board->getTargetAreaTeam(player);
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