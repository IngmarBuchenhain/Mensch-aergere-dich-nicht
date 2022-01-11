#ifndef MAEDN_CLASS_TEST_UI_HPP
#define MAEDN_CLASS_TEST_UI_HPP

// This is only for testing! Not necessarily clean code! Only rudimentary to check logic development

#include <iostream>
#include "CppIUI.hpp"

class TestUI : public IUI
{
    bool exportWanted = false;
    bool exitWanted = false;
    int countTest = 0;
    IBoardUI_SPTR boardCache;
    int state = 0;

public:
    void initBoard(IBoardUI_SPTR board) override
    {
        boardCache = board;
        showState();
        std::vector<std::vector<IGamePieceUI_SPTR>> pieces = boardCache->getGamePieces();
        updateBoard(pieces);
    }

public:
    /**
     * Presents some information to user.
     */
    void showInformation(std::string message) override
    {
        std::cout << std::endl
                  << "Message: " << message << std::endl
                  << std::flush;
    }
    bool exportIsWanted() override
    {

        return exportWanted;
    }

public:
    /**
     * Ask/Make the current player to roll the dice.
     * Does not real produces a number, but simply provides interaction with user and maybe animation..
     */
    void rollDice(int currentPlayer, int diceNumber) override
    {
        std::cout << std::endl
                  << "Player " << currentPlayer << ": It's your turn! If you want to roll the dice, press 'Enter'";
        //  std::cin.ignore(10);
        //std::cin.ignore();
        std::cout << std::endl
                  << "Great! You rolled a -" << diceNumber << "-" << std::endl
                  << std::flush;
    }

    void rollDice(std::string currentPlayer, int diceNumber) override
    {
        std::cout << std::endl
                  << currentPlayer << ": It's your turn! If you want to roll the dice, press 'Enter'";
        //  std::cin.ignore(10);
        countTest++;
        if (countTest > 5000)
        {
            std::cout << "Do you want to quit and save game? 'y' if yes anything else either";
            char exit;
            std::cin >> exit;
            if (exit == 'y')
            {
                exitWanted = true;
                exportWanted = true;
            }
        }
        std::cin.ignore();
        std::cout << std::endl
                  << "You rolled a -" << diceNumber << "-" << std::endl
                  << std::flush;
    }

public:
    /**
     * Present the current player all game pieces he can walk with, and let him choose one.
     */

    IGamePieceUI_SPTR chooseGamePiece(std::vector<IGamePieceUI_SPTR> &gamePieces, int currentPlayer) override
    {
        return gamePieces[0];
    }

public:
    std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> chooseOneGamePiece(std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces, int currentPlayer) override
    {
        //printDebug("In converter");
        std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> result;
        //printDebug("Not chosen");
        std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>>::iterator it = possiblePieces.begin();
        while (it != possiblePieces.end())
        {
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
    std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> chooseOneGamePiece(std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces, std::string currentPlayer) override
    {
        //printDebug("In converter");
        std::cout << currentPlayer << ": Choose which piece to move!" << std::endl;
        std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> result;
        //printDebug("Not chosen");
        std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>>::iterator it = possiblePieces.begin();
        while (it != possiblePieces.end())
        {
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
    // void showStats(std::shared_ptr<Statistics> stats) override
    // {
    //     stats->showDiceStats();
    // }

    bool exitIsWanted() override
    {
        return exitWanted;
    }

    void showWinners(std::vector<std::string> winners) override
    {
        if (winners.size() == 1)
        {
            std::cout << std::endl
                      << "The winner is: " << winners[0] << std::endl;
        }
        else
        {
            std::cout << std::endl
                      << "The winners are: " << std::endl;
        }
        for (int i = 0; i < winners.size(); i++)
        {
            std::cout << i + 1 << ".: " << winners[i] << std::endl;
        }
    }
    /**
     * Updates the drawn board game with changed game pieces.
     * Must call 'initBoard'-method first!
     * Throws exception if no board was initialized!
     */
    // virtual bool updateBoard(std::vector<IGamePieceUI_SPTR> &gamePieces) = 0;
    void updateBoard(std::vector<std::vector<IGamePieceUI_SPTR>> gamePieces) override
    {
        std::cout << std::endl
                  << "State " << state << ":";
        for (int i = 0; i < gamePieces.size(); i++)
        {
            std::cout << std::endl
                      << " Player " << i << ": ";
            for (int index = 0; index < gamePieces[i].size(); index++)
            {
                int pos = gamePieces[i][index]->getPosition();
                if (pos < 10)
                {
                    std::cout << " " << gamePieces[i][index]->getPosition(); // << " ";
                }
                else
                {
                    std::cout << gamePieces[i][index]->getPosition(); // << " ";
                }
                if (gamePieces[i][index]->isInTargetArea())
                {
                    std::cout << " T ";
                }
                else
                {
                    std::cout << " X ";
                }
            }
        }
        std::cout << std::endl
                  << std::flush;
        state++;
    }

    void showState()
    {
        std::cout << std::endl
                  << "Board information: " << std::endl
                  << "Fields: " << boardCache->getNumberOfFields()
                  << " - Number of Homes: " << boardCache->getNumberOfHomes()
                  << " - Number of Players: " << boardCache->getNumberOfPlayers()
                  << " - Number of Pieces per Player: " << boardCache->getNumberOfGamePiecesPerPlayer()
                  << " - Start Fields: ";
        for (int i = 0; i < boardCache->getStartfields().size(); i++)
        {
            std::cout << boardCache->getStartfields()[i] << " - ";
        }
        std::cout << std::endl
                  << std::flush;
    }

public:
    /**
     * Present the stats. 
     */
    void showDiceStats(std::shared_ptr<Statistics> stats) override
    {
        std::cout << std::endl
                  << "Dice statistics" << std::endl;
        std::cout << "Number of total dice rolls: " << stats->getNumberOfTotalRolls() << std::endl;
        std::cout << "Dice distribution:" << std::endl;
        for (int diceNumber = 1; diceNumber < 7; diceNumber++)
        {
            std::cout << diceNumber << ": ";
            // Make it align
            if (stats->getNumberRolls(diceNumber) < 100 && stats->getNumberRolls(diceNumber) > 9)
            {
                std::cout << " ";
            }
            else if (stats->getNumberRolls(diceNumber) < 10)
            {
                std::cout << "  ";
            }
            std::cout << stats->getNumberRolls(diceNumber) << " ";

            // Normalize for bars
            double normalizedNumber = ((double)stats->getNumberRolls(diceNumber) / (double)stats->getNumberOfTotalRolls()) * 400;
            int temp = (int)normalizedNumber;
            // Show bars
            for (int index = 0; index < temp; index++)
            {
                std::cout << "\u25A0";
            }
            std::cout << std::endl;
        }
    }
};

#endif