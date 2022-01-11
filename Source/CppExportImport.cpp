#include "CppExportImport.hpp"

#include <fstream>
#include <filesystem>

#include "CppDebugHelper.hpp"

namespace maednhelper
{
    bool loadFile(std::string fileName, std::shared_ptr<GameConfig> config, std::shared_ptr<GameState> state)
    {
        if(config == nullptr){
            config.reset(new GameConfig());
        }
        std::string line;
        std::ifstream maednfile(fileName);
        if (maednfile.is_open())
        {
            printDebug("File open");
            int count = 0; // Count the lines

            getline(maednfile, line);
            config->homes = std::stoi(line);
            getline(maednfile, line);
            config->players = std::stoi(line);
            getline(maednfile, line);
            config->pieces = std::stoi(line);
            getline(maednfile, line);
            config->rules = std::stoi(line);
            getline(maednfile, line);
            config->fillKI = std::stoi(line);
            getline(maednfile, line);
            config->spread = std::stoi(line);

            // Get names
            while (count < 6)
            {
                getline(maednfile, line);
                if (!line.empty())
                {
                    config->names.push_back(line);
                }
                count++;
            }
            count = 0; // Reset line count

            // Check if a state is provided or only configuration
            getline(maednfile, line);

            if (std::stoi(line) == 1)
            {

                getline(maednfile, line);

                state->stats.reset(new Statistics());
                for (int number = 0; number < std::stoi(line); number++)
                {
                    state->stats->addDiceRoll(1);
                }
                getline(maednfile, line);
                for (int number = 0; number < std::stoi(line); number++)
                {
                    state->stats->addDiceRoll(2);
                }
                getline(maednfile, line);
                for (int number = 0; number < std::stoi(line); number++)
                {
                    state->stats->addDiceRoll(3);
                }
                getline(maednfile, line);
                for (int number = 0; number < std::stoi(line); number++)
                {
                    state->stats->addDiceRoll(4);
                }
                getline(maednfile, line);
                for (int number = 0; number < std::stoi(line); number++)
                {
                    state->stats->addDiceRoll(5);
                }
                getline(maednfile, line);
                for (int number = 0; number < std::stoi(line); number++)
                {
                    state->stats->addDiceRoll(6);
                }
                getline(maednfile, line);
                state->currentPlayer = std::stoi(line);
                getline(maednfile, line);
                state->idOfLastPiece = std::stoi(line);
                getline(maednfile, line);
                int numberOfPieces = std::stoi(line);

                while (count < numberOfPieces)
                {
                    // Get piece states
                    std::shared_ptr<GamePieceState> pieceState;
                    pieceState.reset(new GamePieceState());

                    getline(maednfile, line);

                    pieceState->id = std::stoi(line);
                    getline(maednfile, line);

                    pieceState->position = std::stoi(line);
                    getline(maednfile, line);

                    pieceState->inTargetArea = std::stoi(line);
                    getline(maednfile, line);

                    pieceState->finished = std::stoi(line);

                    state->pieceStates.push_back(pieceState);
                    count++;
                }
                maednfile.close();
                return true;
            }
            else
            {
                printDebug("We have no state");
                maednfile.close();
                return false;
            }
        }
        else
        {
            throw new io_exception;
        }
    }

    void saveFile(std::shared_ptr<GameConfig> config, std::shared_ptr<GameState> state)
    {
        if(config == nullptr || state == nullptr){
            throw new argument_nullptr_exception;
        }
        std::vector<std::shared_ptr<GamePieceState>> pieces = state->pieceStates;
        int currentPlayer = state->currentPlayer;
        int lastPieceID = state->idOfLastPiece;
        std::shared_ptr<Statistics> stats = state->stats;

        std::string fileName = "maedngame";
        std::string tempFileName = fileName;
        int fileCount = 1;

        // Don't overwrite existing files
        while (std::filesystem::exists(tempFileName))
        {
            tempFileName = fileName;
            tempFileName.append(std::to_string(fileCount));
            fileCount++;
        }
        fileName = tempFileName;

        std::ofstream maednfile;
        maednfile.open(fileName);

        maednfile << config->homes << std::endl;
        maednfile << config->players << std::endl;
        maednfile << config->pieces << std::endl;
        maednfile << config->rules << std::endl;
        maednfile << config->fillKI << std::endl;
        maednfile << config->spread << std::endl;
        for (int index = 0; index < 6; index++)
        {
            if (index < config->names.size())
            {
                maednfile << config->names[index] << std::endl;
            }
            else
            {
                maednfile << std::endl;
            }
        }

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
            std::shared_ptr<GamePieceState> currentPiece = pieces[inIndex];
            maednfile << currentPiece->id << std::endl;
            maednfile << currentPiece->position << std::endl;
            maednfile << currentPiece->inTargetArea << std::endl;
            maednfile << currentPiece->finished << std::endl;
        }

        maednfile.close();
    }

}