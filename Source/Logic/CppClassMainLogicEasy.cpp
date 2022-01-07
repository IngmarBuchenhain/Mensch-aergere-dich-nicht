#include "CppClassMainLogicEasy.hpp"
#include "CppDebugHelper.hpp"

#include "CppClassKI.hpp"

#include<iostream>

/** *************************************
 * Constructors of MainLogicDefault     *
 * *************************************/

MainLogicEasy::MainLogicEasy(IUI_SPTR uiObject) : MainLogicBase(uiObject)
{

}

MainLogicEasy::MainLogicEasy(IUI_SPTR uiObject, int numberOfHomes, int numberOfPlayers, int numberOfPieces, bool fillWithKI, bool spreadOnBoard, std::vector<std::string> playerNames) : MainLogicBase(uiObject, numberOfHomes, numberOfPlayers, numberOfPieces, fillWithKI, spreadOnBoard, playerNames){

}


// MainLogicDefault::MainLogicDefault(IUI_SPTR uiObject)
// {
//     if (uiObject == nullptr)
//     {
//         throw argument_nullptr_exception();
//     }
//     ui = uiObject;

//     // Default: So 4 homes, 4 players, 4 pieces per player: Default constructor
//     board.reset(new Board());

//     // Default: So all rules to false: Default constructor
//     rules = std::make_unique<RuleSet>();

//     // Init dice
//     dice = std::make_unique<Dice>();

//     // Roll the start player
//     currentPlayer = dice->getStartPlayer(board->getNumberOfPlayers());

//     // Init stats object
//     stats = std::make_unique<Statistics>();

//     // Init KI.
//     int countHuman = 1;
//     for (int index = 0; index < board->getNumberOfHomes(); index++)
//     {
//         kiPlayer[index] = nullptr;
//         std::string name = "StealthPlayer ";
//         name.append(std::to_string(countHuman));

//         nameOfPlayers.push_back(name);
//         countHuman += 1;
//         //kiPlayer[index] = std::make_unique<KI>(board->getEndFields()[index], board->getNumberOfFields()); // for Debug
//     }
// }

// MainLogicDefault::MainLogicDefault(IUI_SPTR uiObject, int numberOfHomes, int numberOfPlayers, int numberOfPieces, bool fillWithKI, bool spreadOnBoard, std::vector<std::string> playerNames)
// {
//     if (uiObject == nullptr)
//     {
//         throw argument_nullptr_exception();
//     }
//     ui = uiObject;

//     if (numberOfPlayers < 1 || numberOfPlayers > 6 || (numberOfHomes != 4 && numberOfHomes != 6) || numberOfHomes < numberOfPlayers || (numberOfPieces != 3 && numberOfPieces != 4))
//     {
//         throw illegal_argument();
//     }

//     // Default: So 4 homes, 4 players, 4 pieces per player

//     // Check if there are less players than homes. If so, check if, filled with KI is true. If not, check if spreadOnBoard is true
//     int numberOfAllPlayers = numberOfPlayers;
//     for (int index = 0; index < numberOfPlayers; index++)
//     {

//         kiPlayer[index] = nullptr;
//     }
//     if (numberOfPlayers < numberOfHomes)
//     {
//         if (fillWithKI)
//         {
//             // Note which are KI and which not

//             // Set numberOfPlayers to numberOfHomes
//             numberOfAllPlayers = numberOfHomes;

//             // Mark which ones are KI and mark names right
//         }
//     }

//     board.reset(new Board(numberOfHomes == 4 ? false : true, numberOfAllPlayers, numberOfPieces, spreadOnBoard));
//     // Individual rules

//     rules = std::make_unique<RuleSet>(); // Default

//     dice = std::make_unique<Dice>();
//     currentPlayer = dice->getStartPlayer(board->getNumberOfPlayers());
//     stats = std::make_unique<Statistics>();
//     if (fillWithKI)
//     {
//         for (int index = numberOfPlayers; index < numberOfHomes; index++)
//         {
//             kiPlayer[index] = std::make_unique<KI>(board->getEndFields()[index], board->getNumberOfFields());
//         }
//     }
//     if (playerNames.size() < numberOfAllPlayers)
//     {
//         int countKI = 1;
//         int countHuman = 1;
//         for (int index = playerNames.size(); index < numberOfAllPlayers; index++)
//         {
//             if (kiPlayer[index] != nullptr)
//             {
//                 std::string name = "ThenotsointelligentbutluckyKI ";
//                 name.append(std::to_string(countKI));
//                 playerNames.push_back(name);
//                 countKI += 1;
//             }
//             else
//             {
         
//                 std::string name = "StealthPlayer ";
//                 name.append(std::to_string(countHuman));
  
//                 playerNames.push_back(name);
//                 countHuman += 1;
//             }
//         }
//     }
//     nameOfPlayers = playerNames;
// }

/** *************************************
 * Public methods of MainLogicDefault   *
 * *************************************/

void MainLogicEasy::startGame()
{
    for(int i = 0; i < nameOfPlayers.size(); i++){
        std::cout << nameOfPlayers[i] << std::endl;
    }
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
                    lastGamePiece = std::dynamic_pointer_cast<IGamePiece>(selection.first);
                    if (lastGamePiece == nullptr)
                    {
                        printDebug("Bad");
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

/** *************************************
 * Private methods of MainLogicDefault  *
 * *************************************/

std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> MainLogicEasy::getGamePiecesWithNewPositions(int diceRoll, IGamePiece_SPTR lastPiece)
{
    std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> walkAblePieces;
    std::vector<IGamePiece_SPTR> team = board->getTeam(currentPlayer);
    bool alreadyFinished = false;
    for (int pieceIndex = 0; pieceIndex < team.size(); pieceIndex++)
    {
        // printDebug("Current piece ID to check possibilites");

        IGamePiece_SPTR currentPiece = team[pieceIndex];
        // printDebug(currentPiece->getID());
        // printDebug(currentPiece->getPosition());
        if (alreadyFinished)
        {
            break;
        }
        if (lastPiece != nullptr)
        {
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
            if(checkIfFree(team, start)){
 std::pair<int, bool> position;
            position.first = start;
            position.second = false;
            possibilities.push_back(position);
            }
           
        }
        else
        {
            // No 6 or not an
            // Get possibilities
            bool getPossibilities = true;
            if (diceRoll == 6 && board->getHomeAreaTeam(currentPlayer).size() != 0)
            {

                getPossibilities = false;
            }
            if (getPossibilities)
            {
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
