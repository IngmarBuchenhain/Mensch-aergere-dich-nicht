#ifndef MAEDN_CLASS_BOARD_HPP
#define MAEDN_CLASS_BOARD_HPP

#include "CppIBoard.hpp"

#include "CppClassGamePiece.hpp"
#include "CppClassJumpPair.hpp"

/**
 * Representation of the board game. Not "only" the board itself but the full stacked board with game pieces.
 * Holds also the configuraton of the game, i.e. number of players, number of game pieces per player and how many players are possible.
 */
class Board : public IBoard
{
  /** *************************************
   * Members of Board                     *
   * *************************************/

  int numberOfWalkingFields;

  int numberOfHomes;

  std::vector<IJumpPair_SPTR> jumpFields;
  std::vector<int> startFields;
  std::vector<int> endFields;

  std::vector<std::vector<IGamePiece_SPTR>> teamsAndGamePieces;

  /****************************************
   * Constructors of Board                *
   * *************************************/

public:
  Board();

public:
  Board(bool bigField, int numberOfPlayers, int numberOfPieces, bool spreadOnBoard);

  /** *************************************
   * Public methods of Board              *
   * *************************************/

public:
  int getNumberOfFields() override;

public:
  int getNumberOfPlayers() override;

public:
  int getNumberOfGamePiecesPerPlayer() override;

public:
  int getNumberOfHomes() override;

public:
  std::vector<int> getStartfields() override;

public:
  std::vector<int> getEndFields() override;

public:
  std::vector<IJumpPair_SPTR> getJumpFields() override;

public:
  std::vector<std::vector<IGamePieceUI_SPTR>> getGamePieces() override;

public:
  std::vector<IGamePiece_SPTR> getTeam(int player) override;

public:
  std::vector<IGamePiece_SPTR> getTargetAreaTeam(int player) override;

public:
  std::vector<IGamePiece_SPTR> getHomeAreaTeam(int player) override;

public:
  std::vector<IGamePiece_SPTR> getOutsideTeam(int player) override;
};

#endif