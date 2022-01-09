#ifndef MAEDN_STRUCT_STATES_HPP
#define MAEDN_STRUCT_STATES_HPP

#include <vector>

#include "CppClassStatistics.hpp"

struct GamePieceState
{
    int id;
    bool finished;
    bool inTargetArea;
    int position;
};

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

struct GameState
{
    int currentPlayer;
    int idOfLastPiece;
    std::vector<std::shared_ptr<GamePieceState>> pieceStates;
    std::shared_ptr<Statistics> stats;
};

#endif