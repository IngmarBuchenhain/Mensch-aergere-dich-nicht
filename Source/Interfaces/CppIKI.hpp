#ifndef MAEDN_I_KI_HPP
#define MAEDN_I_KI_HPP

#include <map>
#include <vector>
#include <utility>

#include "CppIGamePieceUI.hpp"

/**
 * Interface to provide computer opponents.
 */
class IKI
{
public:
    /**
     * Chooses one of the given GamePieces with one of its moves.
     */
    virtual std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> chooseGamePiece(std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces) = 0;
};

#endif