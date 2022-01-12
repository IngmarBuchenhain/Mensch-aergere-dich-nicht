#include "CppDebugHelper.hpp"

#include <iostream>
#include <vector>

/**
 * Easily switch for whole application using this DebugHelper printing of debug messages.
 * Should be true only while developing.
 */
extern const bool DEBUG = true;

/**
 * Easily switch for whole application using this DebugHelper printing of error messages.
 * Should be always true, messages are for end user also.
 */
extern const bool ERROR = true;

/**
 * Prints the given message to std::cout if in DEBUG-mode.
 * Use for control.
 * DEBUG-mode is switched in implementaion of DebugHelper.
 */
void printDebug(std::string message)
{
    if (DEBUG)
    {
        std::cout << std::endl
                  << "DEBUG: " << message << std::flush;
    }
}

void printDebug(int message)
{
    if (DEBUG)
    {
        std::cout << std::endl
                  << "DEBUG: " << message << std::flush;
    }
}

void printDebug(std::vector<int> message)
{
    if (DEBUG)
    {
        std::cout << std::endl
                  << "DEBUG: ";
        for (int index = 0; index < message.size(); index++)
        {
            std::cout << message[index] << " - ";
        }
        std::cout << std::flush;
    }
}

/**
 * Prints the given message to std::cout if in ERROR-mode.
 * Use for errors. 
 * ERROR-mode is switched in implementaion of DebugHelper.
 * ERROR-mode should always be on, so use message which can be presented to end user.
 */
void printError(std::string message)
{
    if (ERROR)
    {
        std::cerr << std::endl
                  << "ERROR: " << message << std::flush;
    }
}

/**
 * Prints the given message and description of exception to std::cout if in ERROR-mode.
 * Use for errors.
 * ERROR-mode is switched in implementaion of DebugHelper.
 * ERROR-mode should always be on, so use message which can be presented to end user.
 */
void printError(std::string message, std::exception &ex)
{
    if (ERROR)
    {
        std::cerr << std::endl
                  << "ERROR: " << message << " " << ex.what() << " " << std::flush;
    }
}