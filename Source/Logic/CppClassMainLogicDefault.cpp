#include "CppClassMainLogicDefault.hpp"
#include "CppDebugHelper.hpp"

#include "CppClassKI.hpp"

/** *************************************
 * Constructors of MainLogicDefault     *
 * *************************************/

MainLogicDefault::MainLogicDefault(IUI_SPTR uiObject) : MainLogicBase(uiObject)
{
rules = std::make_unique<RuleSet>(); // Default
printDebug("Config not loade?");
config->rules = 0;
}

MainLogicDefault::MainLogicDefault(IUI_SPTR uiObject, int numberOfHomes, int numberOfPlayers, int numberOfPieces, bool fillWithKI, bool spreadOnBoard, std::vector<std::string> playerNames) : MainLogicBase(uiObject, numberOfHomes, numberOfPlayers, numberOfPieces, fillWithKI, spreadOnBoard, playerNames){
rules = std::make_unique<RuleSet>(); // Default
printDebug("Config not loade?");
config->rules = 0;
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


/** *************************************
 * Private methods of MainLogicDefault  *
 * *************************************/

std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> MainLogicDefault::getGamePiecesWithNewPositions(int diceRoll, IGamePiece_SPTR lastPiece)
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
