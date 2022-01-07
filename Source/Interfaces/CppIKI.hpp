#ifndef MAEDN_I_KI_HPP
#define MAEDN_I_KI_HPP


/**
 * Interface to provide computer opponents
 */
class IKI
{
public:
    virtual std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> chooseGamePiece(std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces) = 0;
};

#endif