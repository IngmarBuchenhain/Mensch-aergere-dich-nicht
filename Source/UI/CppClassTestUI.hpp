#ifndef MAEDN_CLASS_TEST_UI_HPP
#define MAEDN_CLASS_TEST_UI_HPP

#include "CppIUI.hpp"

class TestUI : public IUI {
    bool exportWanted = false;
    int countTest = 0;
    IBoardUI_SPTR boardCache;
    int state = 0;
    public:
     void initBoard(IBoardUI_SPTR board){
         boardCache = board;
         showState();
         std::vector<std::vector<IGamePieceUI_SPTR>> pieces = boardCache->getGamePieces();
         updateBoard(pieces);
     }


public:
    /**
     * Presents some information to user.
     */
     void showInformation(std::string message){
         std::cout << std::endl << "Message: " << message << std::endl << std::flush;
     }
    bool exportIsWanted() override{
        return exportWanted;
    }

// public:
//     /**
//      * Presents the given number to the user. NOT NECESSARY?
//      */
//     virtual void showDice(int diceNumber) = 0;


public:
    /**
     * Ask/Make the current player to roll the dice.
     * Does not real produces a number, but simply provides interaction with user and maybe animation..
     */

     void rollDice(int currentPlayer, int diceNumber){
         std::cout << std::endl << "Player " << currentPlayer << ": It's your turn! If you want to roll the dice, press 'Enter'";
       //  std::cin.ignore(10);
         //std::cin.ignore();
         std::cout << std::endl << "Great! You rolled a -" << diceNumber << "-" << std::endl << std::flush;
     }

          void rollDice(std::string currentPlayer, int diceNumber){
         std::cout << std::endl << currentPlayer << ": It's your turn! If you want to roll the dice, press 'Enter'";
       //  std::cin.ignore(10);
         std::cin.ignore();
         std::cout << std::endl << "You rolled a -" << diceNumber << "-" << std::endl << std::flush;
     }


public:
    /**
     * Present the current player all game pieces he can walk with, and let him choose one.
     */

   IGamePieceUI_SPTR chooseGamePiece(std::vector<IGamePieceUI_SPTR> &gamePieces, int currentPlayer){
       return gamePieces[0];
   }
public:
     std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> chooseOneGamePiece(std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces, int currentPlayer) override{
       //printDebug("In converter");
       std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> result;
       //printDebug("Not chosen");
        std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>>::iterator it = possiblePieces.begin();
        while(it != possiblePieces.end()){
           // printDebug(it->first->getID());
            it++;
        }

       result.first = possiblePieces.begin()->first;
       //printDebug("Assigned piece");
       result.second = possiblePieces.begin()->second[0];
       exportWanted = true;
       //printDebug("Assigned walk");
         return result;
     }
    std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> chooseOneGamePiece(std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces, std::string currentPlayer) override{
               //printDebug("In converter");
               std::cout << currentPlayer << ": Choose which piece to move!" << std::endl;
       std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> result;
       //printDebug("Not chosen");
        std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>>::iterator it = possiblePieces.begin();
        while(it != possiblePieces.end()){
           // printDebug(it->first->getID());
            it++;
        }

       result.first = possiblePieces.begin()->first;
       //printDebug("Assigned piece");
       result.second = possiblePieces.begin()->second[0];
       //printDebug("Assigned walk");
    //    if(countTest > 10){
    //        exportWanted = true;
    //    }
       countTest++;
         return result;
    }


public:
    /**
     * Updates the drawn board game with changed game pieces.
     * Must call 'initBoard'-method first!
     * Throws exception if no board was initialized!
     */

   // virtual bool updateBoard(std::vector<IGamePieceUI_SPTR> &gamePieces) = 0;
     void updateBoard(std::vector<std::vector<IGamePieceUI_SPTR>> gamePieces){
        std::cout << std::endl << "State " << state << ":";
        for(int i = 0; i < gamePieces.size(); i++){
            std::cout << std::endl << " Player " << i << ": ";
            for(int index = 0; index < gamePieces[i].size(); index++){
                int pos = gamePieces[i][index]->getPosition();
                if(pos < 10){
 std::cout << " " << gamePieces[i][index]->getPosition();// << " ";
                } else{
                std::cout << gamePieces[i][index]->getPosition();// << " ";
                }
                if(gamePieces[i][index]->isInTargetArea()){
                    std::cout << " T ";
                }else{
                    std::cout << " X ";
                }
                //std::cout << "GamePiece " << gamePieces[i][index]->getID() << " Position: " << gamePieces[i][index]->getPosition() << " - ";
            }
            //std::cout << std::endl << "           ";
            // for(int index = 0; index < gamePieces[i].size(); index++){

                
            //     if(gamePieces[i][index]->isInTargetArea()){
            //         std::cout << " T ";
            //     }else{
            //         std::cout << " x ";
            //     }
            // }
        }
std::cout << std::endl << std::flush;
        state++;

     }

     void showState(){
         std::cout << std::endl << "Board information: " << std::endl << "Fields: " << boardCache->getNumberOfFields()
            << " - Number of Homes: " << boardCache->getNumberOfHomes() 
            << " - Number of Players: " << boardCache->getNumberOfPlayers()
            << " - Number of Pieces per Player: " << boardCache->getNumberOfGamePiecesPerPlayer()
            << " - Start Fields: ";
            for(int i = 0; i < boardCache->getStartfields().size(); i++){
                std::cout << boardCache->getStartfields()[i] << " - ";
            }
            std::cout << std::endl << std::flush;
     }
};

#endif