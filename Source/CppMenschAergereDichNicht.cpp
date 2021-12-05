#include "CppMenschAergereDichNicht.hpp"
#include "CppDebugHelper.hpp"

/**
 * Main entry point to the application.
 * Creates needed objects and starts the logic.
 */
int main(){
    // Create In-Out-object

    // Create Network-object

    // Create logic-object with In-Out-object and Network-object as parameters

    // Start logic-object
    try{
        printDebug("Now in try");
    } catch(...){
        printError("Failed to start game logic due to unknown Error!");
        return -1;
    }
    return 0;
}