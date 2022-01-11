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
  Board(bool bigField, int numberOfPlayers, int numberOfPieces, bool spreadOnBoard);

  /** *************************************
   * Public methods of Board              *
   * *************************************/

public:
  /**
   * Right now two boards are provided with 40 or 48 fields.
   */
  int getNumberOfFields() override;

public:
  /**
   * This returns human and KI players, so 1-6.
   */
  int getNumberOfPlayers() override;

public:
  /**
   * 3/4 are supported right now.
   */
  int getNumberOfGamePiecesPerPlayer() override;

public:
  /**
   * Correlates with getNumberOfFields. 4/6 homes are provided by the two board sizes.
   */
  int getNumberOfHomes() override;

public:
  /**
   * Return a vector, containing the start fields of all players. Player 0 has index 0 in vector and so on.
   */
  std::vector<int> getStartfields() override;

public:
  /**
   * Return a vector, containing the end fields of all players. Player 0 has index 0 in vector and so on.
   */
  std::vector<int> getEndFields() override;

public:
  /**
   * Return a vector with all pairs of jumping fields.
   */
  std::vector<IJumpPair_SPTR> getJumpFields() override;

public:
  /**
   * All game pieces in a vector. Outer vector is at index 0 pieces of player 0. Inner vector contains all game pieces of one player.
   */
  std::vector<std::vector<IGamePieceUI_SPTR>> getGamePieces() override;

public:
  std::vector<IGamePiece_SPTR> getTeam(int player) override;

public:
  std::vector<IGamePiece_SPTR> getTargetAreaTeam(int player) override;

public:
  std::vector<IGamePiece_SPTR> getHomeAreaTeam(int player) override;

public:
  std::vector<IGamePiece_SPTR> getOutsideTeam(int player) override;

  /** *************************************
   * Private methods of Board             *
   * *************************************/

private:
  /**
   * True if 'player' can be used by public methods safely, otherwise False.
   */
  bool checkValidArguments(int player);
};

#endif