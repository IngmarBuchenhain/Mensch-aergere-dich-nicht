#ifndef MAEDN_STRUCT_STATES_HPP
#define MAEDN_STRUCT_STATES_HPP

#include <vector>

#include "CppClassStatistics.hpp"

/**
 * Simple struct to hold state of a game piece without any complexity
 */
struct GamePieceState
{
    int id;
    bool finished;
    bool inTargetArea;
    int position;
};

/**
 * Simple struct to hold configuration of a game
 */
struct GameConfig
{
    int homes;
    int players;
    int pieces;
    int rules;
    bool fillKI;
    bool spread;
    std::vector<std::string> names;
};

/**
 * Simple struct to hold state of a game
 */
struct GameState
{
    int currentPlayer;
    int idOfLastPiece;
    std::vector<std::shared_ptr<GamePieceState>> pieceStates;
    std::shared_ptr<Statistics> stats;
};

#endif