#include <iostream>

#include "CppDebugHelper.hpp"

#include "CppClassMainLogicDefault.hpp"
#include "CppClassTestUI.hpp"

/**
 * Main entry point to the application.
 * Creates needed objects and starts the logic.
 */
int main(int argc, char **argv)
{
    // Indicator whether exceptions occured. Used to show message to user before exit.
    bool errorsOccured = true;

    // Arguments for game logic to be extracted from application input arguments
    int numberOfHomes = 4;
    int numberOfPlayers = 4;
    int numberOfGamePieces = 4;
    int rules = 0;
    bool fillWithKI = true;
    bool spreadOnField = false;

    std::vector<std::string> playerNames;

    // Try read input arguments and determine what to do next
    if (argc == 1)
    {
        // No arguments were given. Use default rules and default player number/board.
        errorsOccured = false;
    }
    else if (argc >= 7)
    {
        errorsOccured = false;

        // Try interpret input.
        try
        {
            // 1. is programm itself

            // 2. expected board config (4: 4 Homes; 6: 6 Homes)
            numberOfHomes = std::stoi(argv[1]);

            // 3. expected number of players (2-6 depending on 2.)
            numberOfPlayers = std::stoi(argv[2]);

            // 4. expected number of game pieces per player (3/4)
            numberOfGamePieces = std::stoi(argv[3]);

            // 5. expected RuleSet (0: Default; 1: Hard; 2: Easy)
            rules = std::stoi(argv[4]);

            // 6. expected option to fill missing players with KI (0: false; 1: true)
            fillWithKI = std::stoi(argv[5]);

            // 7. expected option to spread players on board (if no KI used)(0: false; 1: true)
            spreadOnField = std::stoi(argv[6]);

            // Everything afterwards is treated as player name
            for (int index = 7; index < argc; index++)
            {
                playerNames.push_back(argv[index]);
            }
        }
        catch (std::exception &ex)
        {
            printError("Failure while reading input arguments of application:", ex);
            errorsOccured = true;
        }
        catch (...)
        {
            printError("Failure while reading input arguments of application due to unknown error");
            errorsOccured = true;
        }
    }
    else
    {
        printError("Failure while reading input arguments of application. Number of arguments is wrong! Use no argument to start default game or arguments according to manual.");
        errorsOccured = true;
    }
    if (!errorsOccured)
    {
        try
        {
            // Create UI-Object
            printDebug("Try to create UI-object");
            IUI_SPTR ui(new TestUI);

            // Create logic object with UI-object as argument
            printDebug("Try to create game-logic-object");
            std::shared_ptr<MainLogicDefault> mainLogic;

            switch (rules)
            {
            case 1:
                throw new not_implemented;
                break;
            case 2:
                throw new not_implemented;
                break;
            default:
                mainLogic.reset(new MainLogicDefault(ui, numberOfHomes, numberOfPlayers, numberOfGamePieces, fillWithKI, spreadOnField, playerNames));
                break;
            }

            // Start game
            printDebug("Try to start game logic");
            mainLogic->startGame();
        }
        catch (not_implemented &ex)
        {
            printError("Failure on start or while running game logic due to:", ex);
            errorsOccured = true;
        }
        catch (unexpected_game_piece &ex)
        {
            printError("Failure on start or while running game logic due to:", ex);
            errorsOccured = true;
        }
        catch (illegal_position &ex)
        {
            printError("Failure on start or while running game logic due to:", ex);
            errorsOccured = true;
        }
        catch (std::exception &ex)
        {
            printError("Failure on start or while running game logic due to:", ex);
            errorsOccured = true;
        }
        catch (...)
        {
            printError("Failure on start or while running game logic due to unknown Error!");
            errorsOccured = true;
        }
    }

    if (errorsOccured)
    {
        // Game was quit not correctly
        printError("Application will be quit. Please try again, ask maintainer or file a bug report.");
        return 1;
    }

    // Game was quit correctly
    return 0;
}