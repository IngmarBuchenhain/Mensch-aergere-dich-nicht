#ifndef DEBUG_HELPER_HPP
#define DEBUG_HELPER_HPP

#include <string>
#include <exception>

/**
 * Prints the given message to std::cout if in DEBUG-mode.
 * Use for control.
 * DEBUG-mode is switched in implementaion of DebugHelper.
 */
void printDebug(std::string message);

/**
 * Prints the given message to std::cout if in ERROR-mode.
 * Use for errors. 
 * ERROR-mode is switched in implementaion of DebugHelper.
 * ERROR-mode should always be on, so use message which can be presented to end user.
 */
void printError(std::string message);

/**
 * Prints the given message and description of exception to std::cout if in ERROR-mode.
 * Use for errors.
 * ERROR-mode is switched in implementaion of DebugHelper.
 * ERROR-mode should always be on, so use message which can be presented to end user.
 */
void printError(std::string message, std::exception &ex);

#endif