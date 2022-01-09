#include "CppExportImport.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>
#include "CppIGamePiece.hpp"
#include "CppClassGamePiece.hpp"
#include "CppIGamePieceUI.hpp"
#include "CppStructsForConfigAndState.hpp"
#include "CppDebugHelper.hpp"

namespace maednhelper
{

    bool maednhelper::loadFile(std::string fileName, GameConfig &config, std::shared_ptr<GameState> state)
    {
        std::string line;
        std::ifstream maednfile(fileName);
        if (maednfile.is_open())
        {
            printDebug("File open");
            int count = 0; // Count the lines

            getline(maednfile, line);
            config.homes = std::stoi(line);
            getline(maednfile, line);
            config.players = std::stoi(line);
            getline(maednfile, line);
            config.pieces = std::stoi(line);
            getline(maednfile, line);
            config.rules = std::stoi(line);
            getline(maednfile, line);
            config.fillKI = std::stoi(line);
            getline(maednfile, line);
            config.spread = std::stoi(line);
            printDebug("config loaeded");
            // Get names
            while (count < 6)
            {
                getline(maednfile, line);
                if(!line.empty()){

               
                config.names.push_back(line);
            }
                count++;
            }
            count = 0;
            // Check if a state is provided
            getline(maednfile, line);
            printDebug("diceRolls");
            if(std::stoi(line) == 1){
                       printDebug("We have state");
 getline(maednfile, line);
 printDebug(line);
 state->stats.reset(new Statistics());
            for(int number = 0; number < std::stoi(line); number++){
                printDebug("We have state");
                state->stats->addDiceRoll(1);
                printDebug("We have state");
            }
            printDebug("We have state");
                        getline(maednfile, line);
            for(int number = 0; number < std::stoi(line); number++){
               state->stats->addDiceRoll(2);
            }
            getline(maednfile, line);
            for(int number = 0; number < std::stoi(line); number++){
                state->stats->addDiceRoll(3);
            }
            getline(maednfile, line);
            for(int number = 0; number < std::stoi(line); number++){
               state->stats->addDiceRoll(4);
            }
                        getline(maednfile, line);
            for(int number = 0; number < std::stoi(line); number++){
                state->stats->addDiceRoll(5);
            }
                        getline(maednfile, line);
            for(int number = 0; number < std::stoi(line); number++){
               state->stats->addDiceRoll(6);
            }
            getline(maednfile, line);
            state->currentPlayer = std::stoi(line);
            getline(maednfile, line);
            state->idOfLastPiece = std::stoi(line);
            getline(maednfile, line);
            int numberOfPieces = std::stoi(line);
            printDebug("DiceRolls finished");
           // int pieceMemberCount = 0;
            while(count < numberOfPieces){
                // Get piece states
                std::shared_ptr<GamePieceState> pieceState;
                pieceState.reset(new GamePieceState());
 
getline(maednfile, line);
printDebug(line);
pieceState->id = std::stoi(line);
getline(maednfile, line);
printDebug(line);
pieceState->position = std::stoi(line);
getline(maednfile, line);
printDebug(line);
pieceState->inTargetArea = std::stoi(line);
getline(maednfile, line);
printDebug(line);
pieceState->finished = std::stoi(line);
                
                
state->pieceStates.push_back(pieceState);
count++;
            }
             maednfile.close();
                return true;
            }else{
                printDebug("We have not state");
                maednfile.close();
                return false;
            }
           
            
        }
        else
        {
//throw
        }
        
    }

   
    

    bool maednhelper::saveFile(std::shared_ptr<GameConfig> config, std::vector<GamePieceState> pieces, int currentPlayer, int lastPieceID, std::shared_ptr<Statistics> stats)
    {
        std::string fileName = "maedngame";
        std::string tempFileName = fileName;
        int fileCount = 1;
        printDebug("Start savFile method");
        while (std::__fs::filesystem::exists(tempFileName))
        {
            tempFileName = fileName;
            tempFileName.append(std::to_string(fileCount));
            fileCount++;
        }
        fileName = tempFileName;
printDebug("1");
        std::ofstream maednfile;
        maednfile.open(fileName);
printDebug("2");
        maednfile << config->homes << std::endl;
        maednfile << config->players << std::endl;
        maednfile << config->pieces << std::endl;
        maednfile << config->rules << std::endl;
        maednfile << config->fillKI << std::endl;
        maednfile << config->spread << std::endl;
        for (int index = 0; index < 6; index++)
        {
            if(index < config->names.size()){
maednfile << config->names[index] << std::endl;
            } else{
                maednfile << std::endl;
            }
            
        }
        printDebug("3");
        maednfile << 1 << std::endl;
        maednfile << stats->getNumberRolls(1) << std::endl;
        maednfile << stats->getNumberRolls(2) << std::endl;
         maednfile << stats->getNumberRolls(3) << std::endl;
          maednfile << stats->getNumberRolls(4) << std::endl;
           maednfile << stats->getNumberRolls(5) << std::endl;
            maednfile << stats->getNumberRolls(6) << std::endl;

        // Now needed: currentPlayer, lastpiece, positions of all pieces
        maednfile << currentPlayer << std::endl;
        maednfile << lastPieceID << std::endl;
        maednfile << pieces.size() << std::endl;

            for (int inIndex = 0; inIndex < pieces.size(); inIndex++)
            {
                GamePieceState currentPiece = pieces[inIndex];
                maednfile << currentPiece.id << std::endl;
                maednfile << currentPiece.position << std::endl;
                maednfile << currentPiece.inTargetArea << std::endl;
                maednfile << currentPiece.finished << std::endl;
            }
        

        maednfile.close();
    }



}