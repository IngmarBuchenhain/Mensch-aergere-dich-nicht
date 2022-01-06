#ifndef MAEDN_CLASS_KI_HPP
#define MAEDN_CLASS_KI_HPP

#include <map>
#include <vector>
#include <utility>

#include "CppIGamePiece.hpp"
#include "CppIKI.hpp"

/**
 * 
 */
class KI : public IKI
{
    std::pair<IGamePiece_SPTR, std::pair<int, bool>> returnValue;
    int playerEndField;
    int numberOfFields;

public:
    KI(int endField, int numberFields);

public:
    std::pair<IGamePiece_SPTR, std::pair<int, bool>> chooseGamePiece(std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces) override;

private:
    bool getBestPieceToWalkIntoTargetArea(std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces);

private:
    bool getBestPieceToWalkInTargetArea(std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces);

private:
    bool getPieceToWalkOnField(std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces);

private:
    bool getBestPieceToWalkOutside(std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces);
    int getDistanceToEnd(int position);
};

#endif