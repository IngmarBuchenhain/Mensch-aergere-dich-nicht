#include <exception>
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
    bool errorsOccured = false;

    int numberOfHomes;
    int numberOfPlayers;
    int numberOfGamePieces;
    int rules;
    bool fillWithKI;
    bool spreadOnField;

    std::vector<std::string> playerNames;

    // Try read input arguments and determine what to do next
    if (argc == 1)
    {
        // No arguments were given. Use default rules and default player number/board.
        try
        {
            // Create UI-Object
            printDebug("Try to create UI-object");
            IUI_SPTR testUI(new TestUI);

            // Create logic object with UI-object as argument
            printDebug("Try to create game-logic-object");
            MainLogicDefault mainLogic(testUI);

            printDebug("Try to start game logic");
            mainLogic.startGame();
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
    else if (argc >= 7)
    {
        // Try interpret input.
        try
        {

            // 1. is programm itself
            // 2. expected board config (0: 4 Homes; 1: 6 Homes)
            numberOfHomes = std::stoi(argv[1]);
            // 3. exptected number of players (2-6 depending on 2.)
            numberOfPlayers = std::stoi(argv[2]);
            // 4. exptected number of game pieces per player
            numberOfGamePieces = std::stoi(argv[3]);
            // 5. exptected RuleSet (0: Default; 1: Hard; 2: Easy)
            rules = std::stoi(argv[4]);

            // Everything afterwards is treated as player name
            for(int index = 7; index < argc; index++){
                playerNames.push_back(argv[index]);
            }
        }
        catch (...)
        {
            printError("Invalid arguments for maedn. Integers required for 2. to 7. argument");
            errorsOccured = true;
        }
  

        // Check number of
        if (!errorsOccured)
        {
            // Start logic-object
            try
            {
                // Create UI-Object
                printDebug("Try to create UI-Object");
                IUI_SPTR testUI(new TestUI);

                // Create Network-Object

                printDebug("Try to create Network-Object");

                // Create logic object with In-Out-object and Network-object as parameters
                printDebug("Try to create game logic");

                //MainLogicDefault mainLogic(testUI);
                MainLogicDefault mainLogic(testUI, numberOfHomes, numberOfPlayers, numberOfGamePieces);
                printDebug("Try to start game logic");
                mainLogic.startGame();
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
    }
    else{
        printError("No valid arguments were given to the application! Use no argument to start default game or arguments according to manual.\nTry again!");
        errorsOccured = true;
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