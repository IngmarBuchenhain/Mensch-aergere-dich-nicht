#ifndef MAEDN_CLASS_EXPORT_IMPORT_HPP
#define MAEDN_CLASS_EXPORT_IMPORT_HPP
#include<vector>
#include "CppIGamePiece.hpp"
#include "CppStructsForConfigAndState.hpp"
#include "CppClassStatistics.hpp"
namespace maednhelper{

void saveFile(std::shared_ptr<GameConfig> config, std::vector<GamePieceState> pieces, int currentPlayer, int lastPieceID, std::shared_ptr<Statistics> stats);

bool loadFile(std::string fileName, GameConfig &config, std::shared_ptr<GameState> state);
}
#endif