#include "CppClassMainUILarge.hpp"

void LARGEUI::clearScreen(std::string visualBoard[21][37])
{
    system("clear");
    printBoard(visualBoard);
}

void LARGEUI::initBoard(IBoardUI_SPTR board)
{
    fieldSize = board->getNumberOfFields();

    numberOfPlayers = board->getNumberOfPlayers();

    numberOfGamePiecesPerPlayer = board->getNumberOfGamePiecesPerPlayer();

    numberOfHomes = board->getNumberOfHomes();

    jumpFields = board->getJumpFields();

    gamePieces = board->getGamePieces();

    startFields = board->getStartfields();

    endFields = board->getEndFields();

    for (int i = 0; i < numberOfPlayers; i++)
    {
        if (startFields[i] == 1)
        {
            colorOrder.push_back(color_red);
        }
        else if (startFields[i] == 13)
        {
            colorOrder.push_back(color_blue);
        }
        else if (startFields[i] == 25)
        {
            colorOrder.push_back(color_yellow);
        }
        else if (startFields[i] == 37)
        {
            colorOrder.push_back(color_green);
        }
        else if (startFields[i] == 49)
        {
            colorOrder.push_back(color_magenta);
        }
        else
        {
            colorOrder.push_back(color_cyan);
        }
    }

    currentDiceRoller = 7;

    //std::cout << startFields[0] << ", " << startFields[1] << ", " << startFields[2] << ", " << startFields[3] << ", " << startFields[4] << ", " << startFields[5] << std::endl;
    //std::cin.ignore();

    clearScreen(visualBoard);

    updateBoard(gamePieces);
}

void LARGEUI::showWinners(std::vector<std::string> winners)
{
    clearScreen(visualBoard);
    ;
    std::cout << std::endl;
    showInformation("Das Spiel ist zu Ende. Hier sind die Gewinner... GLÜCKWUNSCH!", color_green);
    for (int i = 0; i < winners.size(); i++)
    {
        if (i == 0)
        {
            std::cout << color_green << "1. " << winners[i] << color_reset << std::endl;
        }
        else if (i == 1)
        {
            std::cout << color_yellow << "1. " << winners[i] << color_reset << std::endl;
        }
        else if (i == 2)
        {
            std::cout << color_red << "1. " << winners[i] << color_reset << std::endl;
        }
        else
        {

            std::cout << (i + 1) << ". " << winners[i] << std::endl;
        }
    }

    showInformation("Weiter mit ENTER.", color_green);
    std::cin.clear();
    std::cin.get();
    std::cin.ignore(40, '\n');
}

void LARGEUI::updateBoard(std::vector<std::vector<IGamePieceUI_SPTR>> gamePieces)
{
    setUpLargeBoard(72);

    int doubleRed = 0;
    int doubleBlue = 0;
    int doubleYellow = 0;
    int doubleGreen = 0;
    int doubleMagenta = 0;
    int doubleCyan = 0;

    for (int i = 0; i < numberOfPlayers; i++)
    {
        for (int j = 0; j < numberOfGamePiecesPerPlayer; j++)
        {
            if (gamePieces[i][j]->getPosition() == 0)
            {
                int x;
                int y;
                if (startFields[i] == 1)
                {
                    y = houses[gamePieces[i][j]->getID() % 4][0];
                    x = houses[gamePieces[i][j]->getID() % 4][1];
                }
                else if (startFields[i] == 13)
                {
                    y = houses[(gamePieces[i][j]->getID() % 4) + 4][0];
                    x = houses[(gamePieces[i][j]->getID() % 4) + 4][1];
                }
                else if (startFields[i] == 25)
                {
                    y = houses[(gamePieces[i][j]->getID() % 4) + 8][0];
                    x = houses[(gamePieces[i][j]->getID() % 4) + 8][1];
                }
                else if (startFields[i] == 37)
                {
                    y = houses[(gamePieces[i][j]->getID() % 4) + 12][0];
                    x = houses[(gamePieces[i][j]->getID() % 4) + 12][1];
                }
                else if (startFields[i] == 49)
                {
                    y = houses[(gamePieces[i][j]->getID() % 4) + 16][0];
                    x = houses[(gamePieces[i][j]->getID() % 4) + 16][1];
                }
                else
                {
                    y = houses[(gamePieces[i][j]->getID() % 4) + 20][0];
                    x = houses[(gamePieces[i][j]->getID() % 4) + 20][1];
                }

                visualBoard[y][x] = colorOrder[i] + basicField + color_reset;
            }
            else if (gamePieces[i][j]->isInTargetArea())
            {
                int x;
                int y;
                if (startFields[i] == 1)
                {
                    y = finishFields[gamePieces[i][j]->getPosition() - 1][0];
                    x = finishFields[gamePieces[i][j]->getPosition() - 1][1];
                }
                else if (startFields[i] == 13)
                {
                    y = finishFields[gamePieces[i][j]->getPosition() + 3][0];
                    x = finishFields[gamePieces[i][j]->getPosition() + 3][1];
                }
                else if (startFields[i] == 25)
                {
                    y = finishFields[gamePieces[i][j]->getPosition() + 7][0];
                    x = finishFields[gamePieces[i][j]->getPosition() + 7][1];
                }
                else if (startFields[i] == 37)
                {
                    y = finishFields[gamePieces[i][j]->getPosition() + 11][0];
                    x = finishFields[gamePieces[i][j]->getPosition() + 11][1];
                }
                else if (startFields[i] == 49)
                {
                    y = finishFields[gamePieces[i][j]->getPosition() + 15][0];
                    x = finishFields[gamePieces[i][j]->getPosition() + 15][1];
                }
                else
                {
                    y = finishFields[gamePieces[i][j]->getPosition() + 19][0];
                    x = finishFields[gamePieces[i][j]->getPosition() + 19][1];
                }

                visualBoard[y][x] = colorOrder[i] + basicField + color_reset;
            }
            else
            {
                int y = fields[gamePieces[i][j]->getPosition() - 1][0];
                int x = fields[gamePieces[i][j]->getPosition() - 1][1];

                visualBoard[y][x] = colorOrder[i] + basicField + color_reset;

                if (x == 0 && y == 8)
                {
                    doubleRed++;
                }
                if (x == 16 && y == 0)
                {
                    doubleBlue++;
                }
                if (x == 24 && y == 0)
                {
                    doubleYellow++;
                }
                if (x == 36 && y == 12)
                {
                    doubleGreen++;
                }
                if (x == 20 && y == 20)
                {
                    doubleMagenta++;
                }
                if (x == 12 && y == 20)
                {
                    doubleCyan++;
                }

                if (doubleRed > 1)
                {
                    visualBoard[7][0] = color_red + "! " + color_reset;
                }
                if (doubleBlue > 1)
                {
                    visualBoard[0][17] = color_red + "! " + color_reset;
                }
                if (doubleYellow > 1)
                {
                    visualBoard[0][24] = color_red + "! " + color_reset;
                }
                if (doubleGreen > 1)
                {
                    visualBoard[13][36] = color_red + " !" + color_reset;
                }
                if (doubleMagenta > 1)
                {
                    visualBoard[20][19] = color_red + " !" + color_reset;
                }
                if (doubleCyan > 1)
                {
                    visualBoard[20][11] = color_red + " !" + color_reset;
                }
            }
        }
    }
}

void LARGEUI::printBoard(std::string visualBoard[21][37])
{
    // print board
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 37; j++)
        {
            std::cout << visualBoard[i][j];
        }
        std::cout << std::endl;
    }
}

std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> LARGEUI::chooseOneGamePiece(std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces, std::string currentPlayer, int playerNumber, int diceNumberSafe)
{
    std::map<IGamePieceUI_SPTR, std::vector<std::pair<int, bool>>>::iterator it;
    int i = 0;
    for (it = possiblePieces.begin(); it != possiblePieces.end(); it++)
    {
        if (it->first->getPosition() == 0)
        {
            int x;
            int y;
            if (colorOrder[playerNumber] == color_red)
            {
                y = houses[it->first->getID() % 4][0];
                x = houses[it->first->getID() % 4][1];
            }
            else if (colorOrder[playerNumber] == color_blue)
            {
                y = houses[(it->first->getID() % 4) + 4][0];
                x = houses[(it->first->getID() % 4) + 4][1];
            }
            else if (colorOrder[playerNumber] == color_yellow)
            {
                y = houses[(it->first->getID() % 4) + 8][0];
                x = houses[(it->first->getID() % 4) + 8][1];
            }
            else if (colorOrder[playerNumber] == color_green)
            {
                y = houses[(it->first->getID() % 4) + 12][0];
                x = houses[(it->first->getID() % 4) + 12][1];
            }
            else if (colorOrder[playerNumber] == color_magenta)
            {
                y = houses[(it->first->getID() % 4) + 16][0];
                x = houses[(it->first->getID() % 4) + 16][1];
            }
            else
            {
                y = houses[(it->first->getID() % 4) + 20][0];
                x = houses[(it->first->getID() % 4) + 20][1];
            }

            visualBoard[y][x] = colorOrder[playerNumber] + halfField + std::to_string(i + 1) + color_reset;
        }
        else if (it->first->isInTargetArea())
        {
            int x;
            int y;
            if (startFields[playerNumber] == 1)
            {
                y = finishFields[it->first->getPosition() - 1][0];
                x = finishFields[it->first->getPosition() - 1][1];
            }
            else if (startFields[playerNumber] == 13)
            {
                y = finishFields[it->first->getPosition() + 3][0];
                x = finishFields[it->first->getPosition() + 3][1];
            }
            else if (startFields[playerNumber] == 25)
            {
                y = finishFields[it->first->getPosition() + 7][0];
                x = finishFields[it->first->getPosition() + 7][1];
            }
            else if (startFields[playerNumber] == 37)
            {
                y = finishFields[it->first->getPosition() + 11][0];
                x = finishFields[it->first->getPosition() + 11][1];
            }
            else if (startFields[playerNumber] == 49)
            {
                y = finishFields[it->first->getPosition() + 15][0];
                x = finishFields[it->first->getPosition() + 15][1];
            }
            else
            {
                y = finishFields[it->first->getPosition() + 19][0];
                x = finishFields[it->first->getPosition() + 19][1];
            }

            visualBoard[y][x] = colorOrder[playerNumber] + halfField + std::to_string(i + 1) + color_reset;
        }
        else
        {
            int y = fields[it->first->getPosition() - 1][0];
            int x = fields[it->first->getPosition() - 1][1];

            visualBoard[y][x] = colorOrder[playerNumber] + halfField + std::to_string(i + 1) + color_reset;
        }
        i++;
    }

    clearScreen(visualBoard);

    if (diceNumberSafe == 6)
    {
        showInformation("Du hast eine 6.", color_green);
    }
    else
    {
        showInformation("Du kannst " + std::to_string(diceNumberSafe) + " Felder fahren.", color_green);
    }

    showInformation(colorOrder[playerNumber] + currentPlayer + color_green + ": Wähle die Figur mit der du ziehen möchtest. (Zahl eingeben und mit ENTER bestätigen; '0' beendet nach dem Zug das Spiel)", color_green);

    int selection;
    while (!(std::cin >> selection))
    {
        std::cout << color_red << "Bitte gebe einen gültigen Wert an." << color_reset << std::endl;
        std::cin.clear();
        //  std::cin.ignore(100);
        std::cin.get();
    }

    if (selection == 0)
    {
        showInformation("Das Spiel wird nach diesem Spielzug beendet", color_green);
        exitWanted = true;

        showInformation("Wähle die Figur mit der du ziehen möchtest. (Zahl eingeben und mit ENTER bestätigen; '0' beendet nach dem Zug das Spiel)", color_green);
        while (selection <= 0 || selection > possiblePieces.size())
        {
            // std::cin >> selection;
            while (!(std::cin >> selection))
            {
                std::cout << color_red << "Bitte gebe einen gültigen Wert an." << color_reset << std::endl;
                std::cin.clear();
                //std::cin.ignore(100);
                std::cin.get();
            }
            if (selection <= 0 || selection > possiblePieces.size())
            {
                showInformation("Ungültige Eingabe! Wähle die Figur mit der du ziehen möchtest.", color_red);
            }
        }
    }
    else
    {
        while (selection <= 0 || selection > possiblePieces.size())
        {
            showInformation("Ungültige Eingabe! Wähle die Figur mit der du ziehen möchtest.", color_red);
            // std::cin >> selection;
            while (!(std::cin >> selection))
            {
                std::cout << color_red << "Bitte gebe einen gültigen Wert an." << color_reset << std::endl;
                std::cin.clear();
                //  std::cin.ignore(100);
                std::cin.get();
            }
        }
    }

    selection--;

    auto iterator = possiblePieces.begin();
    std::advance(iterator, selection);

    selection = 0;

    if (iterator->second.size() > 1)
    {
        showInformation("Rückwärts (0) Vorwärts (1) laufen?", color_green);
        //std::cin >> selection;
        while (!(std::cin >> selection))
        {
            std::cout << color_red << "Bitte gebe einen gültigen Wert an." << color_reset << std::endl;
            std::cin.clear();
            //std::cin.ignore(100);
            std::cin.get();
        }

        if (selection == 0)
        {
            if (iterator->second[0] > iterator->second[1])
            {
                selection = 1;
            }
            else
            {
                selection = 0;
            }
        }
        else
        {
            if (iterator->second[0] > iterator->second[1])
            {
                selection = 0;
            }
            else
            {
                selection = 1;
            }
        }
    }

    std::pair<IGamePieceUI_SPTR, std::pair<int, bool>> output{iterator->first, iterator->second[selection]};

    if (exitWanted == true && !exportWanted)
    {
        selection = 0;
        clearScreen(visualBoard);
        showInformation("Willst du den aktuellen Spielstand speichern? Ja: 1", color_red);
        // std::cin >> selection;
        while (!(std::cin >> selection))
        {
            std::cout << color_red << "Bitte gebe einen gültigen Wert an." << color_reset << std::endl;
            std::cin.clear();
            //std::cin.ignore(100);
            std::cin.get();
        }
        if (selection == 1)
        {
            exportWanted = true;
        }
    }

    return output;
}

void LARGEUI::showInformation(std::string message, std::string color)
{
    std::cout << std::endl
              << color << message << color_reset << std::endl;
}

void LARGEUI::showInformation(std::string message)
{
    std::cout << std::endl
              << color_red << message << color_reset << std::endl;
}

void LARGEUI::rollDiceKI(std::string currentPlayer, int playerNumber, int diceNumber)
{
    diceNumberSafe = diceNumber;
    clearScreen(visualBoard);

    std::string visualDice[9][9];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i == 0 || i == 8 || j == 0 || j == 8)
            {
                visualDice[i][j] = basicField;
            }
            else
            {
                visualDice[i][j] = "  ";
            }
        }
    }

    std::string diceMessage;
    switch (diceNumber)
    {
    case 1:
        visualDice[4][4] = basicField;
        diceMessage = " hat eine Eins gewürfelt";
        break;
    case 2:
        visualDice[6][2] = basicField;
        visualDice[2][6] = basicField;
        diceMessage = " hat eine Zwei gewürfelt";
        break;
    case 3:
        visualDice[6][2] = basicField;
        visualDice[4][4] = basicField;
        visualDice[2][6] = basicField;
        diceMessage = " hat eine Drei gewürfelt";
        break;
    case 4:
        visualDice[2][2] = basicField;
        visualDice[6][2] = basicField;
        visualDice[2][6] = basicField;
        visualDice[6][6] = basicField;
        diceMessage = " hat eine Vier gewürfelt";
        break;
    case 5:
        visualDice[2][2] = basicField;
        visualDice[6][2] = basicField;
        visualDice[4][4] = basicField;
        visualDice[2][6] = basicField;
        visualDice[6][6] = basicField;
        diceMessage = " hat eine Fünf gewürfelt";
        break;

    default:
        visualDice[2][2] = basicField;
        visualDice[4][2] = basicField;
        visualDice[6][2] = basicField;
        visualDice[2][6] = basicField;
        visualDice[4][6] = basicField;
        visualDice[6][6] = basicField;
        diceMessage = " hat eine Sechs gewürfelt";
        break;
    }

    std::cout << std::endl;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            std::cout << visualDice[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << std::endl
              << colorOrder[playerNumber] << currentPlayer << color_reset << diceMessage << color_green << std::endl
              << "Drücke 1+ENTER um fortzufahren oder 0+ENTER um einen Spielabbruch nach dem Zug anzufordern." << color_reset << std::endl;

    // std::cout << std::endl
    //           << colorOrder[playerNumber] << currentPlayer << color_reset << ", du bist an der Reihe zu würfeln." << std::endl
    //           << color_green << "Drücke 1+ENTER um fortzufahren oder 0+ENTER um einen Spielabbruch nach dem Zug anzufordern." << color_reset << std::endl;

    //     std::cin.clear();
    //     int testtesttest = 0;
    //     while(testtesttest != 1){
    // std::cin >> testtesttest; //std::cin.get();
    //     if(std::cin.fail()){
    //         testtesttest = 0;
    //     }
    //     std::cin.clear();

    // }
    waitForUser();
    if (exitWanted == true && !exportWanted)
    {
        clearScreen(visualBoard);
        showInformation("Willst du den aktuellen Spielstand speichern? Ja: 1", color_red);
        int selection = 0;
        while (!(std::cin >> selection))
        {
            std::cout << color_red << "Bitte gebe einen gültigen Wert an." << color_reset << std::endl;
            std::cin.clear();
            //std::cin.ignore(100);
            std::cin.get();
        }
        if (selection == 1)
        {
            exportWanted = true;
        }
    }

    // std::cin.clear();
    // std::cin.get();
    // std::cin.ignore(40, '\n');
}

void LARGEUI::rollDice(std::string currentPlayer, int playerNumber, int diceNumber)
{
    if (diceNumberSafe == 6)
    {
        showInformation("Du darfst nochmal würfeln. ENTER.", color_green);
        std::cin.clear();
        std::cin.get();
    }

    if (playerNumber != currentDiceRoller && currentDiceRoller != 7)
    {
        currentDiceRoller = playerNumber;
        int helper = 0;
        showInformation(colorOrder[playerNumber] + currentPlayer + color_green + " ist nun an der Reihe. Berei? Dann bestätige mit der (1).", color_green);
        //std::cin >> helper;
        while (!(std::cin >> helper))
        {
            std::cout << color_red << "Bitte gebe einen gültigen Wert an." << color_reset << std::endl;
            std::cin.clear();
            //std::cin.ignore(100);
            std::cin.get();
        }
        while (helper != 1)
        {
            showInformation(colorOrder[playerNumber] + currentPlayer + color_red + ": Bitte bestätige mit der Eins (1) und ENTER, dass du bereit bist.", color_red);

            while (!(std::cin >> helper))
            {
                std::cout << color_red << "Bitte gebe einen gültigen Wert an." << color_reset << std::endl;
                std::cin.clear();
                // std::cin.ignore(100);
                std::cin.get();
            }
            // std::cin >> helper;
        }
    }

    diceNumberSafe = diceNumber;
    clearScreen(visualBoard);

    std::cout << std::endl;
    std::string visualDice[9][9];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i == 0 || i == 8 || j == 0 || j == 8)
            {
                visualDice[i][j] = basicField;
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
            std::cout << colorOrder[playerNumber] << visualDice[i][j];
        }
        std::cout << color_reset << std::endl;
    }

    std::cout << std::endl
              << colorOrder[playerNumber] << currentPlayer << color_reset << ", du bist an der Reihe zu würfeln." << std::endl
              << color_green << "Drücke 1+ENTER um fortzufahren oder 0+ENTER um einen Spielabbruch nach dem Zug anzufordern." << color_reset << std::endl;

    //     std::cin.clear();
    //     int testtesttest = 0;
    //     while(testtesttest != 1){
    // std::cin >> testtesttest; //std::cin.get();
    //     if(std::cin.fail()){
    //         testtesttest = 0;
    //     }
    //     std::cin.clear();

    // }
    waitForUser();

    clearScreen(visualBoard);
    ;

    std::string diceMessage;
    switch (diceNumber)
    {
    case 1:
        visualDice[4][4] = basicField;
        diceMessage = "Du hast eine Eins gewürfelt. Ist das Alles?";
        break;
    case 2:
        visualDice[6][2] = basicField;
        visualDice[2][6] = basicField;
        diceMessage = "Nur weil es Augenzahl heißt, heißt das nicht, dass du nur ein Zwei würfeln darfst.";
        break;
    case 3:
        visualDice[6][2] = basicField;
        visualDice[4][4] = basicField;
        visualDice[2][6] = basicField;
        diceMessage = "Wir kommen der Sache schon näher.";
        break;
    case 4:
        visualDice[2][2] = basicField;
        visualDice[6][2] = basicField;
        visualDice[2][6] = basicField;
        visualDice[6][6] = basicField;
        diceMessage = "Immerhin mehr als Drei.";
        break;
    case 5:
        visualDice[2][2] = basicField;
        visualDice[6][2] = basicField;
        visualDice[4][4] = basicField;
        visualDice[2][6] = basicField;
        visualDice[6][6] = basicField;
        diceMessage = "Wenn du dir jetzt denkst 'so knapp' hast du wohl nie in Mathe aufgepasst.";
        break;

    default:
        visualDice[2][2] = basicField;
        visualDice[4][2] = basicField;
        visualDice[6][2] = basicField;
        visualDice[2][6] = basicField;
        visualDice[4][6] = basicField;
        visualDice[6][6] = basicField;
        diceMessage = "Whooooo!!! EINE SECHS!!!";
        break;
    }

    std::cout << std::endl;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            std::cout << colorOrder[playerNumber] << visualDice[i][j];
        }
        std::cout << color_reset << std::endl;
    }

    std::cout << std::endl
              << color_red << diceMessage << color_green << std::endl
              << "Drücke 1+ENTER um fortzufahren oder 0+ENTER um einen Spielabbruch nach dem Zug anzufordern." << color_reset << std::endl;

    // std::cin.clear();
    // std::cin.get();
    waitForUser();
    if (exitWanted == true && !exportWanted)
    {
        clearScreen(visualBoard);
        showInformation("Willst du den aktuellen Spielstand speichern? Ja: 1", color_red);
        int selection = 0;
        while (!(std::cin >> selection))
        {
            std::cout << color_red << "Bitte gebe einen gültigen Wert an." << color_reset << std::endl;
            std::cin.clear();
            //std::cin.ignore(100);
            std::cin.get();
        }
        if (selection == 1)
        {
            exportWanted = true;
        }
    }
}

void LARGEUI::setUpLargeBoard(int fieldSize)
{
    // 1 - 12
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

    fields[5][0] = 8;
    fields[5][1] = 10;

    fields[6][0] = 8;
    fields[6][1] = 12;

    fields[7][0] = 6;
    fields[7][1] = 12;

    fields[8][0] = 4;
    fields[8][1] = 12;

    fields[9][0] = 2;
    fields[9][1] = 12;

    fields[10][0] = 0;
    fields[10][1] = 12;

    fields[11][0] = 0;
    fields[11][1] = 14;

    // 13 - 24
    fields[12][0] = 0;
    fields[12][1] = 16;

    fields[13][0] = 2;
    fields[13][1] = 16;

    fields[14][0] = 4;
    fields[14][1] = 16;

    fields[15][0] = 6;
    fields[15][1] = 16;

    fields[16][0] = 8;
    fields[16][1] = 16;

    fields[17][0] = 8;
    fields[17][1] = 18;

    fields[18][0] = 8;
    fields[18][1] = 20;

    fields[19][0] = 6;
    fields[19][1] = 20;

    fields[20][0] = 4;
    fields[20][1] = 20;

    fields[21][0] = 2;
    fields[21][1] = 20;

    fields[22][0] = 0;
    fields[22][1] = 20;

    fields[23][0] = 0;
    fields[23][1] = 22;

    // 25 - 36
    fields[24][0] = 0;
    fields[24][1] = 24;

    fields[25][0] = 2;
    fields[25][1] = 24;

    fields[26][0] = 4;
    fields[26][1] = 24;

    fields[27][0] = 6;
    fields[27][1] = 24;

    fields[28][0] = 8;
    fields[28][1] = 24;

    fields[29][0] = 8;
    fields[29][1] = 26;

    fields[30][0] = 8;
    fields[30][1] = 28;

    fields[31][0] = 8;
    fields[31][1] = 30;

    fields[32][0] = 8;
    fields[32][1] = 32;

    fields[33][0] = 8;
    fields[33][1] = 34;

    fields[34][0] = 8;
    fields[34][1] = 36;

    fields[35][0] = 10;
    fields[35][1] = 36;

    // 37 - 48
    fields[36][0] = 12;
    fields[36][1] = 36;

    fields[37][0] = 12;
    fields[37][1] = 34;

    fields[38][0] = 12;
    fields[38][1] = 32;

    fields[39][0] = 12;
    fields[39][1] = 30;

    fields[40][0] = 12;
    fields[40][1] = 28;

    fields[41][0] = 12;
    fields[41][1] = 26;

    fields[42][0] = 12;
    fields[42][1] = 24;

    fields[43][0] = 14;
    fields[43][1] = 24;

    fields[44][0] = 16;
    fields[44][1] = 24;

    fields[45][0] = 18;
    fields[45][1] = 24;

    fields[46][0] = 20;
    fields[46][1] = 24;

    fields[47][0] = 20;
    fields[47][1] = 22;

    // 49 - 60
    fields[48][0] = 20;
    fields[48][1] = 20;

    fields[49][0] = 18;
    fields[49][1] = 20;

    fields[50][0] = 16;
    fields[50][1] = 20;

    fields[51][0] = 14;
    fields[51][1] = 20;

    fields[52][0] = 12;
    fields[52][1] = 20;

    fields[53][0] = 12;
    fields[53][1] = 18;

    fields[54][0] = 12;
    fields[54][1] = 16;

    fields[55][0] = 14;
    fields[55][1] = 16;

    fields[56][0] = 16;
    fields[56][1] = 16;

    fields[57][0] = 18;
    fields[57][1] = 16;

    fields[58][0] = 20;
    fields[58][1] = 16;

    fields[59][0] = 20;
    fields[59][1] = 14;

    // 61 - 72
    fields[60][0] = 20;
    fields[60][1] = 12;

    fields[61][0] = 18;
    fields[61][1] = 12;

    fields[62][0] = 16;
    fields[62][1] = 12;

    fields[63][0] = 14;
    fields[63][1] = 12;

    fields[64][0] = 12;
    fields[64][1] = 12;

    fields[65][0] = 12;
    fields[65][1] = 10;

    fields[66][0] = 12;
    fields[66][1] = 8;

    fields[67][0] = 12;
    fields[67][1] = 6;

    fields[68][0] = 12;
    fields[68][1] = 4;

    fields[69][0] = 12;
    fields[69][1] = 2;

    fields[70][0] = 12;
    fields[70][1] = 0;

    fields[71][0] = 10;
    fields[71][1] = 0;

    // red
    houses[0][0] = 3;
    houses[0][1] = 0;
    houses[1][0] = 3;
    houses[1][1] = 2;
    houses[2][0] = 5;
    houses[2][1] = 0;
    houses[3][0] = 5;
    houses[3][1] = 2;
    // blue
    houses[4][0] = 0;
    houses[4][1] = 7;
    houses[5][0] = 0;
    houses[5][1] = 9;
    houses[6][0] = 2;
    houses[6][1] = 7;
    houses[7][0] = 2;
    houses[7][1] = 9;
    // yellow
    houses[8][0] = 0;
    houses[8][1] = 27;
    houses[9][0] = 0;
    houses[9][1] = 29;
    houses[10][0] = 2;
    houses[10][1] = 27;
    houses[11][0] = 2;
    houses[11][1] = 29;
    // green
    houses[12][0] = 15;
    houses[12][1] = 34;
    houses[13][0] = 15;
    houses[13][1] = 36;
    houses[14][0] = 17;
    houses[14][1] = 34;
    houses[15][0] = 17;
    houses[15][1] = 36;
    // magenta
    houses[16][0] = 18;
    houses[16][1] = 27;
    houses[17][0] = 18;
    houses[17][1] = 29;
    houses[18][0] = 20;
    houses[18][1] = 27;
    houses[19][0] = 20;
    houses[19][1] = 29;
    // cyan
    houses[20][0] = 18;
    houses[20][1] = 7;
    houses[21][0] = 18;
    houses[21][1] = 9;
    houses[22][0] = 20;
    houses[22][1] = 7;
    houses[23][0] = 20;
    houses[23][1] = 9;

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
    finishFields[4][1] = 14;
    finishFields[5][0] = 4;
    finishFields[5][1] = 14;
    finishFields[6][0] = 6;
    finishFields[6][1] = 14;
    finishFields[7][0] = 8;
    finishFields[7][1] = 14;
    //yellow
    finishFields[8][0] = 2;
    finishFields[8][1] = 22;
    finishFields[9][0] = 4;
    finishFields[9][1] = 22;
    finishFields[10][0] = 6;
    finishFields[10][1] = 22;
    finishFields[11][0] = 8;
    finishFields[11][1] = 22;
    //green
    finishFields[12][0] = 10;
    finishFields[12][1] = 34;
    finishFields[13][0] = 10;
    finishFields[13][1] = 32;
    finishFields[14][0] = 10;
    finishFields[14][1] = 30;
    finishFields[15][0] = 10;
    finishFields[15][1] = 28;
    //magenta
    finishFields[16][0] = 18;
    finishFields[16][1] = 22;
    finishFields[17][0] = 16;
    finishFields[17][1] = 22;
    finishFields[18][0] = 14;
    finishFields[18][1] = 22;
    finishFields[19][0] = 12;
    finishFields[19][1] = 22;
    //cyan
    finishFields[20][0] = 18;
    finishFields[20][1] = 14;
    finishFields[21][0] = 16;
    finishFields[21][1] = 14;
    finishFields[22][0] = 14;
    finishFields[22][1] = 14;
    finishFields[23][0] = 12;
    finishFields[23][1] = 14;

    // set spaces
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 37; j++)
        {
            visualBoard[i][j] = "  ";
        }
    }

    // set normal fields
    for (int i = 0; i < 72; i++)
    {
        visualBoard[fields[i][0]][fields[i][1]] = basicField;
    }

    // set background of houses
    for (int i = 0; i < 24; i = i + 4)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (i == 0)
                {
                    visualBoard[houses[i][0] + j][houses[i][1] + k] = color_red + lightField + color_reset;
                }
                else if (i == 4)
                {
                    visualBoard[houses[i][0] + j][houses[i][1] + k] = color_blue + lightField + color_reset;
                }
                else if (i == 8)
                {
                    visualBoard[houses[i][0] + j][houses[i][1] + k] = color_yellow + lightField + color_reset;
                }
                else if (i == 12)
                {
                    visualBoard[houses[i][0] + j][houses[i][1] + k] = color_green + lightField + color_reset;
                }
                else if (i == 16)
                {
                    visualBoard[houses[i][0] + j][houses[i][1] + k] = color_magenta + lightField + color_reset;
                }
                else
                {
                    visualBoard[houses[i][0] + j][houses[i][1] + k] = color_cyan + lightField + color_reset;
                }
            }
        }
    }

    // set houses
    for (int i = 0; i < 24; i++)
    {
        if (i < 4)
        {
            visualBoard[houses[i][0]][houses[i][1]] = basicField;
        }
        else if (i < 8)
        {
            visualBoard[houses[i][0]][houses[i][1]] = basicField;
        }
        else if (i < 12)
        {
            visualBoard[houses[i][0]][houses[i][1]] = basicField;
        }
        else
        {
            visualBoard[houses[i][0]][houses[i][1]] = basicField;
        }
    }

    // set startpoints
    visualBoard[fields[0][0]][fields[0][1]] = color_red + lightField + color_reset;
    visualBoard[fields[12][0]][fields[12][1]] = color_blue + lightField + color_reset;
    visualBoard[fields[24][0]][fields[24][1]] = color_yellow + lightField + color_reset;
    visualBoard[fields[36][0]][fields[36][1]] = color_green + lightField + color_reset;
    visualBoard[fields[48][0]][fields[48][1]] = color_magenta + lightField + color_reset;
    visualBoard[fields[60][0]][fields[60][1]] = color_cyan + lightField + color_reset;

    // set finishFields
    for (int i = 0; i < 24; i++)
    {
        if (i < 4)
        {
            visualBoard[finishFields[i][0]][finishFields[i][1]] = color_red + lightField + color_reset;
        }
        else if (i < 8)
        {
            visualBoard[finishFields[i][0]][finishFields[i][1]] = color_blue + lightField + color_reset;
        }
        else if (i < 12)
        {
            visualBoard[finishFields[i][0]][finishFields[i][1]] = color_yellow + lightField + color_reset;
        }
        else if (i < 16)
        {
            visualBoard[finishFields[i][0]][finishFields[i][1]] = color_green + lightField + color_reset;
        }
        else if (i < 20)
        {
            visualBoard[finishFields[i][0]][finishFields[i][1]] = color_magenta + lightField + color_reset;
        }
        else
        {
            visualBoard[finishFields[i][0]][finishFields[i][1]] = color_cyan + lightField + color_reset;
        }
    }

    if (numberOfGamePiecesPerPlayer == 3)
    {
        visualBoard[finishFields[3][0]][finishFields[3][1]] = "  ";
        visualBoard[finishFields[7][0]][finishFields[7][1]] = "  ";
        visualBoard[finishFields[11][0]][finishFields[11][1]] = "  ";
        visualBoard[finishFields[15][0]][finishFields[15][1]] = "  ";
        visualBoard[finishFields[19][0]][finishFields[19][1]] = "  ";
        visualBoard[finishFields[23][0]][finishFields[23][1]] = "  ";
    }

    visualBoard[8][8] = lightField;
    visualBoard[8][16] = lightField;
    visualBoard[8][24] = lightField;
    visualBoard[12][28] = lightField;
    visualBoard[12][20] = lightField;
    visualBoard[12][12] = lightField;
}

bool LARGEUI::exitIsWanted()
{
    return exitWanted;
}

bool LARGEUI::exportIsWanted()
{
    return exportWanted;
}

void LARGEUI::waitForUser()
{
    int input;
    while (!(std::cin >> input) || (input != 0 && input != 1))
    {
        std::cout << color_red << "Bitte gebe einen gültigen Wert an (0 für Spielabbruch nach Zug oder 1 für Weiter)." << color_reset << std::endl;
        std::cin.clear();
        //std::cin.ignore(100);
        std::cin.get();
    }
    if (input == 0)
    {
        showInformation("Das Spiel wird nach diesem Spielzug beendet", color_green);
        exitWanted = true;
    }
}

void LARGEUI::showDiceStats(std::shared_ptr<Statistics> stats)
{
    clearScreen(visualBoard);
    std::cout << std::endl
              << "Würfel Statistik" << std::endl;
    std::cout << "Anzahl Gesamtwürfe: " << stats->getNumberOfTotalRolls() << std::endl;
    std::cout << "Würfel-Verteilung:" << std::endl;
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
        double normalizedNumber = ((double)stats->getNumberRolls(diceNumber) / (double)stats->getNumberOfTotalRolls()) * 250;
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
    
    ;
    system("clear");
    return 0;
}
*/
