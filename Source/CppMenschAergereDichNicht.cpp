#include "CppDebugHelper.hpp"
#include "CppExportImport.hpp"

#include "CppClassMainLogicDefault.hpp"
#include "CppClassMainLogicHard.hpp"
#include "CppClassMainLogicEasy.hpp"

#include "CppClassTestUI.hpp"

#include "CppStructsForConfigAndState.hpp"

/**
 * Main entry point to the application.
 * Creates needed objects and starts the logic.
 */
int main(int argc, char **argv)
{
    // Indicator whether exceptions occured. Used to show message to user before exit.
    bool errorsOccured = true;
    // Indicator whether a game was loaded.
    bool loadedGame = false;

    // Arguments for game logic to be extracted from application input arguments with default configuration
    // Default configuration to be altered if wanted before start
    std::shared_ptr<GameConfig> config = std::make_shared<GameConfig>();
    config->homes = 4;
    config->players = 4;
    config->pieces = 4;
    config->rules = 0;
    config->fillKI = true;
    config->spread = false;

    // State in case game is loaded from file
    std::shared_ptr<GameState> state = std::make_shared<GameState>();

    // Try read input arguments and determine what to do next
    if (argc == 1)
    {
        // No arguments were given. Use default rules and default player number/board.
        errorsOccured = false;
    }
    else if (argc == 2)
    {
        // We expect a config file was given. Either this is a game imported or only the config for a new game.
        errorsOccured = false;

        try
        {
            std::string fileName = argv[1];

            printDebug("Load file");
            // Load config and if there state for game. If it also contains state note this.
            if (maednhelper::loadFile(fileName, config, state))
            {
                loadedGame = true;
            }
        }
        catch (std::exception &ex)
        {
            printError("Failure while reading configuration file due to:", ex);
            errorsOccured = true;
        }
        catch (...)
        {
            printError("Failure while reading configuration file due to unknown error");
            errorsOccured = true;
        }
    }
    else if (argc >= 7)
    {
        errorsOccured = false;

        // Try interpret input. "Wrong" values can be put into the config. The Logic class deals with wrong input
        try
        {
            // 1. is programm itself

            // 2. expected board config (4: 4 Homes; 6: 6 Homes)
            config->homes = std::stoi(argv[1]);

            // 3. expected number of players (2-6 depending on 2.)
            config->players = std::stoi(argv[2]);

            // 4. expected number of game pieces per player (3/4)
            config->pieces = std::stoi(argv[3]);

            // 5. expected RuleSet (0: Default; 1: Hard; 2: Easy)
            config->rules = std::stoi(argv[4]);

            // 6. expected option to fill missing players with KI (0: false; 1: true)
            config->fillKI = std::stoi(argv[5]);

            // 7. expected option to spread players on board (if no KI used)(0: false; 1: true)
            config->spread = std::stoi(argv[6]);

            // Everything afterwards is treated as player name
            int count = 0;
            for (int index = 7; index < argc; index++)
            {
                count += 1;
                if (count <= config->players)
                {
                    config->names.push_back(argv[index]);
                }
                else
                {
                    break;
                }
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

            // Create logic object with UI-object and config as argument
            printDebug("Try to create game-logic-object");
            std::shared_ptr<MainLogicBase> mainLogic;

            switch (config->rules)
            {
            case 1:
                mainLogic.reset(new MainLogicHard(ui, config));
                break;
            case 2:
                mainLogic.reset(new MainLogicEasy(ui, config));
                break;
            default:
                printDebug("Default rules");
                mainLogic.reset(new MainLogicDefault(ui, config));
                break;
            }
            if (loadedGame)
            { // If we loaded the game from file we have to set the positions and states of the game pieces
                printDebug("Import game state");
                mainLogic->importGameState(state->pieceStates, state->currentPlayer, state->idOfLastPiece, state->stats);
            }
            // Start game
            printDebug("Try to start game logic");
            mainLogic->startGame();
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