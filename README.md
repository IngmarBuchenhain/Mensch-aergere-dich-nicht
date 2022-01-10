# Mensch-aergere-dich-nicht
This is a simple board game known by most people which can be played by CLI.

## Wish list

### Must Have

- [x] General game logic
- [x] Default rules
- [x] 1 - 4 players (Because of the simple KI you can also play alone with your computer now)
- [x] Some 'graphical' representation of the game in the CLI

### Should Have

- [x] 1 - 6 players/Bigger board (Because of the simple KI you can also play alone with your computer now)
- [x] Export/Import game
- [x] Different rules (Default, Easy, Hard)
- [x] Hints to which game piece can be choosen (Only those are presented to user now)

### Nice to Have

- [x] Simple KI
- [ ] Network multiplayer (Delayed for future release)
## How to play
### Dependencies
- GCC with g++ if use of provided MAKEFILE is wanted
### Build the game
1. Load repository (main branch or one of the releases)
2. Run 'make' in 'Source'-directory. You can provide a path to which the executable ('maedn') should be build via 'make outpath=path/you/like'
3. With 'make run' you can run a quick pre-configured game
### Run the game
The settings of the game are selected by CL-argument or by configuration file. Once the game started you can not change settings but has to restart (You should never change rules of a game midway anyways...).
1. Configure game and run: This is done by command line arguments to the game executable. Following options
    - None: Pre-configured default game (not like 'make run'!): 4 Homes, 4 Players, 4 Pieces, Default rules
    - 6 or more (not counting the app itself): Starts an individual game. The six arguments are integers as followed in order. Everything after that are strings with players names.
        1. 4/6 - Number of Homes (Small or big board)
        2. 1-6 - Number of (human) players. Note: More players than homes won't work ;-)
        3. 3/4 - Number of game pieces per player
        4. 0-2 - RuleSet (0: Default; 1: Hard; 2: Easy)
        5. 0/1 - Fill remaining homes with KI-players (0: No; 1: Yes)
        6. 0/1 - Spread players on board (0: No; 1: Yes)(Only if not filled with KI and sensible to spread)
    - One: This must be a file in same directory (or a path). This must hold the same arguments like the 6 arguments, each in one line. Each name in a new line. With this you can have multiple configuration files to quickly start games. (See also sample file in 'Demo'-directory 'maedngame' for configuration only and 'maedngame1' for a save-file)
2. You can run via 'make run' a pre-configured game (4 Homes, 3 Players (Torsten, Niklas, Ingmar), 4 Pieces each, Default rules, Fill remaining homes with KI)
3. You can load a saved game with one CL-argument too: If you have exported a game state before, just take this file as CL-argument. It will hold game configuration and state.
4. If you are in the game you can exit the game and save the state if you wish. The saved file ('maedngame' or if already there with a number following will hold configuration and state of the game)
- See also in 'Demo'-directory for explanation of config/state-file
## Rule Sets
This game offers 3 different rule sets you can choose from. Use the number in brackets in the input arguments or the configuration file.
Choose wisely!
### General rules
Apply to all rule sets:
- If no piece is on the field you are allowed to roll the dice 3 times until you get a 6.
### Default: Boring Default Rules (0)
    EVERYTHING FALSE
     bool mustThrowOtherPiecesIntern;
    bool mustThrowOwnPiecesIntern;
    bool throwAlsoBackwardsIntern;

    bool jumpOverPiecesInTargetAreaIntern;
    bool walkByTargetAreaIfNotPossibleToWalkInIntern;

    bool saveOnStartFieldIntern;
    bool mustAlwaysFreeStartFieldIntern; // evtl weglassen, da im goWithAnother.. einbegriffen werden kann.
    bool allowedToUseOutsidePieceOnSixWhenPiecesLeftHomeIntern;

    bool onlyRollThreeTimesIfNoPieceOutAndTargetAreaOnEndIntern;

    bool jumpOnEdgesIntern;

    bool goWithAnotherPieceOnSecondRollOfDiceIntern;

    bool playUntilAllPlayersFinishedIntern;

Kein Schlagzwang
Eigene Figuren werden nicht geschlagen
Startfeld muss freigemacht werden, solange noch männchen im haus oder wenn wieder imhaus
Bei 6: Es muss neue Figur ins Spiel gebracht werden. Wenn mit eigener besetzt, dann erst diese mit 6 weiterziehen und dann nochmal würfeln. Wenn nochmal würfeln mus mit gleicher figur gezogen werden.
Warten vor loch
im zilel darf übersprungen werden
3 mal würfeln wenn nix geht

Zusätze:
Rückwärts schlagen
Springen an Ecken
Selbst rausschmeißen
schlagzwang
### Easy: For Wimps (Or Children) (1)
 bool mustThrowOtherPiecesIntern;   False
    bool mustThrowOwnPiecesIntern;False
    bool throwAlsoBackwardsIntern;False

    bool jumpOverPiecesInTargetAreaIntern;True
    bool walkByTargetAreaIfNotPossibleToWalkInIntern;False

    bool saveOnStartFieldIntern;True
    bool mustAlwaysFreeStartFieldIntern; False// evtl weglassen, da im goWithAnother.. einbegriffen werden kann.
    bool allowedToUseOutsidePieceOnSixWhenPiecesLeftHomeIntern;True

    bool onlyRollThreeTimesIfNoPieceOutAndTargetAreaOnEndIntern;False

    bool jumpOnEdgesIntern;False

    bool goWithAnotherPieceOnSecondRollOfDiceIntern;True

    bool playUntilAllPlayersFinishedIntern;False
    false, false, false, true, false, true, false, true, false, false, true, false
### Hard: Only For The Real Players (2)

 bool mustThrowOtherPiecesIntern; True
    bool mustThrowOwnPiecesIntern; True
    bool throwAlsoBackwardsIntern; True

    bool jumpOverPiecesInTargetAreaIntern;False
    bool walkByTargetAreaIfNotPossibleToWalkInIntern; True

    bool saveOnStartFieldIntern; False
    bool mustAlwaysFreeStartFieldIntern; true// evtl weglassen, da im goWithAnother.. einbegriffen werden kann.
    bool allowedToUseOutsidePieceOnSixWhenPiecesLeftHomeIntern;false

    bool onlyRollThreeTimesIfNoPieceOutAndTargetAreaOnEndIntern;true

    bool jumpOnEdgesIntern;true

    bool goWithAnotherPieceOnSecondRollOfDiceIntern;false

    bool playUntilAllPlayersFinishedIntern;true
true, true, true, false, true, false, true, false, true, true ,false, true

Must-Throw other pieces: Yes
Must-Throw own pieces (only if no other possibility): Yes
Throw also backwards: Yes
Jump over pieces in "home"-row: No
Throwable on "Start"-Field: Yes

## Contributors
- [Niklas Arnold](https://github.com/niklasar)
- [Ingmar Bauckhage](https://github.com/IngmarBuchenhain)

## License
[GPLv3 License](https://github.com/IngmarBuchenhain/Mensch-aergere-dich-nicht/blob/a9f37a3aa70579cdb452c9196e7cb0fd8359d22d/LICENSE)
