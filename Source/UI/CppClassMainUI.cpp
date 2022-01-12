#include "CppClassMainUI.hpp"

void UI::initBoard(IBoardUI_SPTR board)
{
    board_ptr = board;

    fieldSize = board->getNumberOfFields();

    numberOfPlayers = board->getNumberOfPlayers();

    numberOfGamePiecesPerPlayer = board->getNumberOfGamePiecesPerPlayer();

    numberOfHomes = board->getNumberOfHomes();

    jumpFields = board->getJumpFields();

    gamePieces = board->getGamePieces();

    updateBoard(gamePieces);

}

 void UI::showWinners(std::vector<std::string> winners){

 }

void UI::updateBoard(std::vector<std::vector<IGamePieceUI_SPTR>> gamePieces)
{
    setUpSmallBoard(40);

    for (int i = 0; i < numberOfPlayers; i++)
    {
        for (int j = 0; j < numberOfGamePiecesPerPlayer; j++)
        {
            if (gamePieces[i][j]->isInTargetArea())
            {
                int x;
                int y;
                if (gamePieces[i][j]->getID() < numberOfGamePiecesPerPlayer)
                {
                    y = finishFields[gamePieces[i][j]->getPosition() - 1][0];
                    x = finishFields[gamePieces[i][j]->getPosition() - 1][1];
                }
                else if (gamePieces[i][j]->getID() < (2 * numberOfGamePiecesPerPlayer))
                {
                    y = finishFields[gamePieces[i][j]->getPosition() + 3][0];
                    x = finishFields[gamePieces[i][j]->getPosition() + 3][1];
                }
                else if (gamePieces[i][j]->getID() < (3 * numberOfGamePiecesPerPlayer))
                {
                    y = finishFields[gamePieces[i][j]->getPosition() + 7][0];
                    x = finishFields[gamePieces[i][j]->getPosition() + 7][1];
                }
                else
                {
                    y = finishFields[gamePieces[i][j]->getPosition() + 11][0];
                    x = finishFields[gamePieces[i][j]->getPosition() + 11][1];
                }

                if (i == 0)
                {
                    visualBoard[y][x] = color_red + "██" + color_reset;
                }
                else if (i == 1)
                {
                    visualBoard[y][x] = color_blue + "██" + color_reset;
                }
                else if (i == 2)
                {
                    visualBoard[y][x] = color_yellow + "██" + color_reset;
                }
                else
                {
                    visualBoard[y][x] = color_green + "██" + color_reset;
                }
            }
            else
            {
                int y = fields[gamePieces[i][j]->getPosition() - 1][0];
                int x = fields[gamePieces[i][j]->getPosition() - 1][1];
                if (i == 0)
                {
                    visualBoard[y][x] = color_red + "██" + color_reset;
                }
                else if (i == 1)
                {
                    visualBoard[y][x] = color_blue + "██" + color_reset;
                }
                else if (i == 2)
                {
                    visualBoard[y][x] = color_yellow + "██" + color_reset;
                }
                else
                {
                    visualBoard[y][x] = color_green + "██" + color_reset;
                }
            }
        }
    }

    // print board
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            std::cout << visualBoard[i][j];
        }
        std::cout << std::endl;
    }
}

std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> UI::chooseOneGamePiece(std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces, std::string currentPlayer, int playerNumber)
{
    std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>>::iterator it;
    int i = 1;
    for (it = possiblePieces.begin(); it != possiblePieces.end(); it++)
    {
        if (it->first->isInTargetArea())
        {
            int x;
            int y;
            if (it->first->getID() < numberOfGamePiecesPerPlayer)
            {
                y = finishFields[it->first->getPosition() - 1][0];
                x = finishFields[it->first->getPosition() - 1][1];
            }
            else if (it->first->getID() < (2 * numberOfGamePiecesPerPlayer))
            {
                y = finishFields[it->first->getPosition() + 3][0];
                x = finishFields[it->first->getPosition() + 3][1];
            }
            else if (it->first->getID() < (3 * numberOfGamePiecesPerPlayer))
            {
                y = finishFields[it->first->getPosition() + 7][0];
                x = finishFields[it->first->getPosition() + 7][1];
            }
            else
            {
                y = finishFields[it->first->getPosition() + 11][0];
                x = finishFields[it->first->getPosition() + 11][1];
            }

            if (i == 0)
            {
                visualBoard[y][x] = color_red + "█" + std::to_string(i) + color_reset;
            }
            else if (i == 1)
            {
                visualBoard[y][x] = color_blue + "█" + std::to_string(i) + color_reset;
            }
            else if (i == 2)
            {
                visualBoard[y][x] = color_yellow + "█" + std::to_string(i) + color_reset;
            }
            else
            {
                visualBoard[y][x] = color_green + "█" + std::to_string(i) + color_reset;
            }
        }
        else
        {
            int y = fields[it->first->getPosition() - 1][0];
            int x = fields[it->first->getPosition() - 1][1];
            if (i == 0)
            {
                visualBoard[y][x] = color_red + "█" + std::to_string(i) + color_reset;
            }
            else if (i == 1)
            {
                visualBoard[y][x] = color_blue + "█" + std::to_string(i) + color_reset;
            }
            else if (i == 2)
            {
                visualBoard[y][x] = color_yellow + "█" + std::to_string(i) + color_reset;
            }
            else
            {
                visualBoard[y][x] = color_green + "█" + std::to_string(i) + color_reset;
            }
        }
        i++;
    }

    showInformation("Wähle die Figur mit der du ziehen möchtest. (Zahl eingeben und mit ENTER bestätigen)");

    int selection;
    std::cin >> selection;

    std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> output{possiblePieces.begin()->first, possiblePieces.begin()->second[0]};

    return output;
}

void UI::showInformation(std::string message)
{
    std::cout << std::endl
              << color_red << message << color_reset << std::endl;
}

void UI::rollDice(std::string currentPlayer, int playerNumber, int diceNumber)
{
    system("clear");

    std::cout << std::endl;
    std::string visualDice[9][9];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i == 0 || i == 8 || j == 0 || j == 8)
            {
                visualDice[i][j] = "██";
            }
            else
            {
                visualDice[i][j] = "  ";
            }
        }
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            std::cout << visualDice[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << std::endl
              << color_red << currentPlayer << color_green << ", du bist an der Reihe zu würfeln." << std::endl
              << "Drücke dazu ENTER." << color_reset << std::endl;

    std::cin.ignore();

    system("clear");

    std::string diceMessage;
    switch (diceNumber)
    {
    case 1:
        visualDice[4][4] = "██";
        diceMessage = "Du hast eine Eins gewürfelt. Ist das Alles?";
        break;
    case 2:
        visualDice[6][2] = "██";
        visualDice[2][6] = "██";
        diceMessage = "Nur weil es Augenzahl heiß, heißt das nicht, dass du auch nur ein Zwei würfeln darfst.";
        break;
    case 3:
        visualDice[6][2] = "██";
        visualDice[4][4] = "██";
        visualDice[2][6] = "██";
        diceMessage = "Wir kommen der Sache schon näher.";
        break;
    case 4:
        visualDice[2][2] = "██";
        visualDice[6][2] = "██";
        visualDice[2][6] = "██";
        visualDice[6][6] = "██";
        diceMessage = "Immerhin mehr als Drei.";
        break;
    case 5:
        visualDice[2][2] = "██";
        visualDice[6][2] = "██";
        visualDice[4][4] = "██";
        visualDice[2][6] = "██";
        visualDice[6][6] = "██";
        diceMessage = "Wenn du dir jetzt denkst 'so knapp' hast du wohl nie in Mathe aufgepasst.";
        break;

    default:
        visualDice[2][2] = "██";
        visualDice[4][2] = "██";
        visualDice[6][2] = "██";
        visualDice[2][6] = "██";
        visualDice[4][6] = "██";
        visualDice[6][6] = "██";
        diceMessage = "Whooooo!!! EINE SECHS!!!";
        break;
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            std::cout << visualDice[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << std::endl
              << color_red << diceMessage << color_green << std::endl
              << "Drücke ENTER um fortzufahren." << color_reset << std::endl;

    std::cin.ignore();
}

void UI::setUpSmallBoard(int fieldSize)
{
    // 1 - 10
    fields[0][0] = 8;
    fields[0][1] = 0;
    fields[1][0] = 8;
    fields[1][1] = 2;
    fields[2][0] = 8;
    fields[2][1] = 4;
    fields[3][0] = 8;
    fields[3][1] = 6;
    fields[4][0] = 8;
    fields[4][1] = 8;
    fields[5][0] = 6;
    fields[5][1] = 8;
    fields[6][0] = 4;
    fields[6][1] = 8;
    fields[7][0] = 2;
    fields[7][1] = 8;
    fields[8][0] = 0;
    fields[8][1] = 8;
    fields[9][0] = 0;
    fields[9][1] = 10;
    // 11 - 20
    fields[10][0] = 0;
    fields[10][1] = 12;
    fields[11][0] = 2;
    fields[11][1] = 12;
    fields[12][0] = 4;
    fields[12][1] = 12;
    fields[13][0] = 6;
    fields[13][1] = 12;
    fields[14][0] = 8;
    fields[14][1] = 12;
    fields[15][0] = 8;
    fields[15][1] = 14;
    fields[16][0] = 8;
    fields[16][1] = 16;
    fields[17][0] = 8;
    fields[17][1] = 18;
    fields[18][0] = 8;
    fields[18][1] = 20;
    fields[19][0] = 10;
    fields[19][1] = 20;
    // 21 - 30
    fields[20][0] = 12;
    fields[20][1] = 20;
    fields[21][0] = 12;
    fields[21][1] = 18;
    fields[22][0] = 12;
    fields[22][1] = 16;
    fields[23][0] = 12;
    fields[23][1] = 14;
    fields[24][0] = 12;
    fields[24][1] = 12;
    fields[25][0] = 14;
    fields[25][1] = 12;
    fields[26][0] = 16;
    fields[26][1] = 12;
    fields[27][0] = 18;
    fields[27][1] = 12;
    fields[28][0] = 20;
    fields[28][1] = 12;
    fields[29][0] = 20;
    fields[29][1] = 10;
    // 31 - 40
    fields[30][0] = 20;
    fields[30][1] = 8;
    fields[31][0] = 18;
    fields[31][1] = 8;
    fields[32][0] = 16;
    fields[32][1] = 8;
    fields[33][0] = 14;
    fields[33][1] = 8;
    fields[34][0] = 12;
    fields[34][1] = 8;
    fields[35][0] = 12;
    fields[35][1] = 6;
    fields[36][0] = 12;
    fields[36][1] = 4;
    fields[37][0] = 12;
    fields[37][1] = 2;
    fields[38][0] = 12;
    fields[38][1] = 0;
    fields[39][0] = 10;
    fields[39][1] = 0;

    // red
    houses[0][0] = 0;
    houses[0][1] = 0;
    houses[1][0] = 0;
    houses[1][1] = 2;
    houses[2][0] = 2;
    houses[2][1] = 0;
    houses[3][0] = 2;
    houses[3][1] = 2;
    // blue
    houses[4][0] = 0;
    houses[4][1] = 18;
    houses[5][0] = 0;
    houses[5][1] = 20;
    houses[6][0] = 2;
    houses[6][1] = 18;
    houses[7][0] = 2;
    houses[7][1] = 20;
    // yellow
    houses[8][0] = 18;
    houses[8][1] = 18;
    houses[9][0] = 18;
    houses[9][1] = 20;
    houses[10][0] = 20;
    houses[10][1] = 18;
    houses[11][0] = 20;
    houses[11][1] = 20;
    // green
    houses[12][0] = 18;
    houses[12][1] = 0;
    houses[13][0] = 18;
    houses[13][1] = 2;
    houses[14][0] = 20;
    houses[14][1] = 0;
    houses[15][0] = 20;
    houses[15][1] = 2;

    //red
    finishFields[0][0] = 10;
    finishFields[0][1] = 2;
    finishFields[1][0] = 10;
    finishFields[1][1] = 4;
    finishFields[2][0] = 10;
    finishFields[2][1] = 6;
    finishFields[3][0] = 10;
    finishFields[3][1] = 8;
    //blue
    finishFields[4][0] = 2;
    finishFields[4][1] = 10;
    finishFields[5][0] = 4;
    finishFields[5][1] = 10;
    finishFields[6][0] = 6;
    finishFields[6][1] = 10;
    finishFields[7][0] = 8;
    finishFields[7][1] = 10;
    //yellow
    finishFields[8][0] = 10;
    finishFields[8][1] = 18;
    finishFields[9][0] = 10;
    finishFields[9][1] = 16;
    finishFields[10][0] = 10;
    finishFields[10][1] = 14;
    finishFields[11][0] = 10;
    finishFields[11][1] = 12;
    //green
    finishFields[12][0] = 18;
    finishFields[12][1] = 10;
    finishFields[13][0] = 16;
    finishFields[13][1] = 10;
    finishFields[14][0] = 14;
    finishFields[14][1] = 10;
    finishFields[15][0] = 12;
    finishFields[15][1] = 10;

    // set spaces
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            visualBoard[i][j] = "  ";
        }
    }

    // set normal fields
    for (int i = 0; i < 40; i++)
    {
        visualBoard[fields[i][0]][fields[i][1]] = "██";
    }

    // set background of houses
    for (int i = 0; i < 16; i = i + 4)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (i == 0)
                {
                    visualBoard[houses[i][0] + j][houses[i][1] + k] = color_red + "▒▒" + color_reset;
                }
                else if (i == 4)
                {
                    visualBoard[houses[i][0] + j][houses[i][1] + k] = color_blue + "▒▒" + color_reset;
                }
                else if (i == 8)
                {
                    visualBoard[houses[i][0] + j][houses[i][1] + k] = color_yellow + "▒▒" + color_reset;
                }
                else
                {
                    visualBoard[houses[i][0] + j][houses[i][1] + k] = color_green + "▒▒" + color_reset;
                }
            }
        }
    }

    // set houses
    for (int i = 0; i < 16; i++)
    {
        if (i < 4)
        {
            visualBoard[houses[i][0]][houses[i][1]] = "██";
        }
        else if (i < 8)
        {
            visualBoard[houses[i][0]][houses[i][1]] = "██";
        }
        else if (i < 12)
        {
            visualBoard[houses[i][0]][houses[i][1]] = "██";
        }
        else
        {
            visualBoard[houses[i][0]][houses[i][1]] = "██";
        }
    }

    // set startpoints
    visualBoard[fields[0][0]][fields[0][1]] = color_red + "▒▒" + color_reset;
    visualBoard[fields[10][0]][fields[10][1]] = color_blue + "▒▒" + color_reset;
    visualBoard[fields[20][0]][fields[20][1]] = color_yellow + "▒▒" + color_reset;
    visualBoard[fields[30][0]][fields[30][1]] = color_green + "▒▒" + color_reset;

    // set finishFields
    for (int i = 0; i < 16; i++)
    {
        if (i < 4)
        {
            visualBoard[finishFields[i][0]][finishFields[i][1]] = color_red + "▒▒" + color_reset;
        }
        else if (i < 8)
        {
            visualBoard[finishFields[i][0]][finishFields[i][1]] = color_blue + "▒▒" + color_reset;
        }
        else if (i < 12)
        {
            visualBoard[finishFields[i][0]][finishFields[i][1]] = color_yellow + "▒▒" + color_reset;
        }
        else
        {
            visualBoard[finishFields[i][0]][finishFields[i][1]] = color_green + "▒▒" + color_reset;
        }
    }
}

bool UI::exitIsWanted()
{
    return exitWanted;
}

bool UI::exportIsWanted()
{
    return exportWanted;
}

void UI::showDiceStats(std::shared_ptr<Statistics> stats)
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
/*
int main() {
    system("clear");
    rollDice("Spieler rot", 4);
    system("clear");
    setUpSmallBoard(40);
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            std::cout << visualBoard[i][j];
        }
        std::cout << std::endl;
    }
    std::cin.ignore();
    system("clear");
    return 0;
}
*/