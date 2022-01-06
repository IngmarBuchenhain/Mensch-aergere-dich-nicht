
#include "CppDebugHelper.hpp"

#include<exception>
#include<iostream>

#include "CppClassMainLogic.hpp"
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

    // Try read input arguments and determine what to do next
    if(argc == 1){
        std::cout << "Test1";
        // No arguments were given. Use default rules and default player number/board. 
    } else if(argc == 2){
        std::cout << "Test2";
        // One argument was given. We expect this to be a configuration file. Try read it. 
        // If possible, use it to start game, otherwise give error.
    } else{
        // We expect that configuration was given directly in arguments. Check for number of arguments and consistancy and start game.
        std::cout << "Test3";
    }

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
        
        MainLogicDefault mainLogic(testUI);

        printDebug("Try to start game logic");
        mainLogic.startGame();
    }
    catch(unexpected_game_piece &ex){
        printError("Failure on start or while running game logic due to:", ex);
        errorsOccured = true;
    }
    catch(illegal_position &ex){
        printError("Failure on start or while running game logic due to:", ex);
        errorsOccured = true;
    }
    catch(std::exception &ex){
        printError("Failure on start or while running game logic due to:", ex);
        errorsOccured = true;
    }
    catch (...)
    {
        printError("Failure on start or while running game logic due to unknown Error!");
        errorsOccured = true;
    }

    if(errorsOccured){
        // Game was quit not correctly
        printError("Application will be quit. Please try again, ask maintainer or file a bug report.");
        return 1;
    }   

    // Game was quit correctly
    return 0;
}