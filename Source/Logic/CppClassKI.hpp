#ifndef MAEDN_CLASS_KI_HPP
#define MAEDN_CLASS_KI_HPP

#include "CppIKI.hpp"

/**
 * Computer opponent with some "intelligent" choosing behaviour. 
 */
class KI : public IKI
{
    /**
     * The GamePiece the KI will choose and return to the logic.
     */
    std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> returnValue;
    int playerEndField;
    int numberOfFields;

public:
    /**
     * Initialize KI with its end field and the number of fields. Does not need to know more about the board.
     */
    KI(int endField, int numberFields);

public:
    /**
     * Chooses one of the given GamePieces with one of its moves.
     */
    std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> chooseGamePiece(std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces) override;

private:
    bool getBestPieceToWalkIntoTargetArea(std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces);

private:
    bool getBestPieceToWalkInTargetArea(std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces);

private:
    bool getPieceToWalkOnField(std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces);

private:
    bool getBestPieceToWalkOutside(std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces);

private:
    /**
     * Get the distance to the end field from a given position in running order. So if end field is 38 and position is 39, number of fields is 40, distance is 39
     */
    int getDistanceToEnd(int position);
};

#endif