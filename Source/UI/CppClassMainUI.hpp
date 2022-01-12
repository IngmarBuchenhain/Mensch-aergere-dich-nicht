#include "CppIUI.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <utility>

class UI:public IUI {

void clearScreen();
void setUpSmallBoard(int fieldSize);
void updateBoard(std::vector<std::vector<IGamePieceUI_SPTR>> gamePieces) override;
void showInformation(std::string message) override;
void initBoard(IBoardUI_SPTR board) override;
std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> chooseOneGamePiece(std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces, std::string currentPlayer, int playerNumber) override;
void rollDice(std::string currentPlayer, int playerNumber, int diceNumber) override;
     bool exitIsWanted() override;
     bool exportIsWanted() override;
     void showDiceStats(std::shared_ptr<Statistics> stats) override;
      void showWinners(std::vector<std::string> winners) override;

std::string color_reset = "\033[0m";
std::string color_red = "\033[31m";
std::string color_blue = "\033[34m";
std::string color_green = "\033[32m";
std::string color_yellow = "\033[33m";

    bool exportWanted = false;
    bool exitWanted = false;

int fields[40][2];
std::string visualBoard[21][21];
int finishFields [16][2];
int houses [16][2];


IBoardUI_SPTR board_ptr;
int fieldSize;
int numberOfPlayers;
int numberOfGamePiecesPerPlayer;
int numberOfHomes;
std::vector<int> startFields;
std::vector<int> endFields;
std::vector<IJumpPair_SPTR> jumpFields;
std::vector<std::vector<IGamePieceUI_SPTR>> gamePieces;

};