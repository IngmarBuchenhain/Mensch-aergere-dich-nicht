#ifndef MAEDN_DEBUG_HELPER_HPP
#define MAEDN_DEBUG_HELPER_HPP

// Used for exceptions and help methods for debugging

#include <string>
#include <exception>
#include <vector>

// Exceptions
class unexpected_game_piece : public std::exception
{
    virtual const char *what() const throw() override
    {
        return "A game piece which was not applicable was used";
    }
};

class illegal_position : public std::exception
{
    virtual const char *what() const throw() override
    {
        return "The position is not on the board";
    }
};

class argument_nullptr_exception : public std::exception
{
    virtual const char *what() const throw() override
    {
        return "The given argument is nullptr!";
    }
};

class illegal_argument : public std::exception
{
    virtual const char *what() const throw() override
    {
        return "The given argument is not valid!";
    }
};

class not_implemented : public std::exception
{
    virtual const char *what() const throw() override
    {
        return "This functionality was not yet implemented!";
    }
};

class io_exception : public std::exception
{
    virtual const char *what() const throw() override
    {
        return "Could not read or write file!";
    }
};

class illegal_gamepiece_operation : public std::exception
{
    virtual const char *what() const throw() override
    {
        return "You are not allowed to use this method because GamePiece is in target area! Use setToTargetArea(..) instead.";
    }
};

/**
 * Prints the given message to std::cout if in DEBUG-mode.
 * Use for control.
 * DEBUG-mode is switched in implementaion of DebugHelper.
 */
void printDebug(std::string message);

/**
 * Prints the given message to std::cout if in DEBUG-mode.
 * Use for control.
 * DEBUG-mode is switched in implementaion of DebugHelper.
 */
void printDebug(int message);

/**
 * Prints the given message to std::cout if in DEBUG-mode.
 * Use for control.
 * DEBUG-mode is switched in implementaion of DebugHelper.
 */
void printDebug(std::vector<int> message);

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