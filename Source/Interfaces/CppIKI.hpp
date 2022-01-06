#ifndef MAEDN_I_KI_HPP
#define MAEDN_I_KI_HPP

//#include <utility>
// #include <map>
// #include <vector>

/**
 * Interface to provide computer opponents
 */
class IKI
{
public:
    virtual std::pair<IGamePiece_SPTR, std::pair<int, bool>> chooseGamePiece(std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces) = 0;
};

#endif