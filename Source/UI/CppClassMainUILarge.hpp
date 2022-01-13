#ifndef MAEDN_UI_LARGE_HPP
#define MAEDN_UI_LARGE_HPP

#include "CppIUI.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <utility>

class LARGEUI:public IUI {

void clearScreen(std::string visualBoard[21][37]);
void printBoard(std::string visualBoard[21][37]);
void setUpLargeBoard(int fieldSize);
void updateBoard(std::vector<std::vector<IGamePieceUI_SPTR>> gamePieces) override;
void showInformation(std::string message) override;
void showInformation(std::string message, std::string color) override;
void initBoard(IBoardUI_SPTR board) override;
std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> chooseOneGamePiece(std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces, std::string currentPlayer, int playerNumber, int diceNumberSafe) override;
void rollDice(std::string currentPlayer, int playerNumber, int diceNumber) override;
void rollDiceKI(std::string currentPlayer,int playerNumber, int diceNumber) override;
bool exitIsWanted() override;
bool exportIsWanted() override;
void showDiceStats(std::shared_ptr<Statistics> stats) override;
void showWinners(std::vector<std::string> winners) override;

std::string color_reset = "\033[0m";
std::string color_red = "\033[31m";
std::string color_blue = "\033[34m";
std::string color_green = "\033[32m";
std::string color_yellow = "\033[33m";
std::string color_magenta = "\033[35m";
std::string color_cyan = "\033[36m";

std::string basicField = "██";
std::string lightField = "▒▒";
std::string halfField = "█";

bool exportWanted = false;
bool exitWanted = false;

int fields[72][2];
std::string visualBoard[21][37];
int finishFields [24][2];
int houses [24][2];


IBoardUI_SPTR board_ptr;
int fieldSize;
int numberOfPlayers;
int numberOfGamePiecesPerPlayer;
int numberOfHomes;
std::vector<int> startFields;
std::vector<int> endFields;
std::vector<IJumpPair_SPTR> jumpFields;
std::vector<std::vector<IGamePieceUI_SPTR>> gamePieces;
std::vector<std::string> colorOrder;
int diceNumberSafe;

};

#endif
