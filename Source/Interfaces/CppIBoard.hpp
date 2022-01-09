#ifndef MAEDN_I_BOARD_HPP
#define MAEDN_I_BOARD_HPP

#include "CppIBoardUI.hpp"
#include "CppIGamePiece.hpp"

class IBoard : public IBoardUI{
    

public:
virtual std::vector<IGamePiece_SPTR> getTeam(int player) = 0;
public:
    virtual std::vector<IGamePiece_SPTR> getTargetAreaTeam(int player) = 0;

    public:
    virtual std::vector<IGamePiece_SPTR> getHomeAreaTeam(int player) = 0;

    public: 
    virtual std::vector<IGamePiece_SPTR> getOutsideTeam(int player) = 0;

};

typedef std::shared_ptr<IBoard> IBoard_SPTR;
//typedef std::unique_ptr<IBoard> IBoard_UPTR;

#endif