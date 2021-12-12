#include "CppMenschAergereDichNicht.hpp"
#include "CppDebugHelper.hpp"

#include "CppILogic.hpp"

#include<exception>

/**
 * Main entry point to the application.
 * Creates needed objects and starts the logic.
 */
int main(int argc, char **argv)
{
    // Indicator whether exceptions occured. Used to show message to user before exit.
    bool errorsOccured = false;

    // Try read input arguments and determine what to do next
    if(argc == 0){

    } else if(argc == 1){

    } else{

    }

    // Start logic-object
    try
    {
        // Create UI-Object

        printDebug("Try to create UI-Object");
            // Create Network-Object

        printDebug("Try to create Network-Object");
            // Create logic-object with In-Out-object and Network-object as parameters
  
        printDebug("Try to create game logic");
        printDebug("Try to start game logic");

        //ILogic ml = MainLogic(42);

        throw std::invalid_argument( "received negative value" );
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