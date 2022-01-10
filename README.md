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
- GCC if use of provided MAKEFILE is wanted
### Build the game
1. Load repository
2. Run 'make' in 'Source'-directory. You can provide a path to which the executable should be build via 'make outpath=path/you/like
### Run the game
The settings of the game are selected by CL-parameters or by configuration file. Once the game started you can not change settings but has to restart (You should never change rules of a game midway...).
There are different options:
- Network or Local // Planned for future
- Number of players
- Number of game pieces
- Ruleset
- Names of players
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
