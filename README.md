# Mensch-aergere-dich-nicht
This is a simple board game known by most people which can be played by CLI.

## Thoughts on development
- Developed for unix-based os (tested on macos 12 (Arm/Intel) and ubuntu 20)
- Start via command line parameters (Different options to configure you individual game)

### Feature Wish list
#### Must Have

- [x] General game logic
- [x] Default rules
- [x] 1 - 4 players (Because of the simple KI you can also play alone with your computer now)
- [x] Some 'graphical' representation of the game in the CLI

#### Should Have

- [x] 1 - 6 players/Bigger board (Because of the simple KI you can also play alone with your computer now)
- [x] Export/Import game
- [x] Different rules (Default, Easy, Hard)
- [x] Hints to which game piece can be choosen (Only those are presented to user now)

#### Nice to Have

- [x] Simple KI
- [ ] Network multiplayer (Delayed for future release)

### Architecture and stuff
Development was implemented to provide independent working on the project, therefore:
1. Have a model/models representating the game/board/gamestate as interface. (Models-Directory). 
2. Split development into UI and Logic. Logic manipulates Model and uses UI to present it to the user and have interactions with user. Concrete implementation of model is also easily replaceable because of interface (UI-Directory/Logic-Directory).
3. Make interfaces on how these modules should work together (Logic uses an UI-interface, so can be easily switched; UI knows the Model via interface to present it to the user when asked by the logic). Different interfaces of model for UI and Logic (UI don't have to know as much as Logic) (Interfaces-Directory).
4. Implement different rule sets by specialized logic classes. With this approach it is easier to implement new rule variations.
5. Implement different board sizes (UI) with different UI-classes as they can be easily switched in logic.
5. Model consist of Board with GamePieces. In addition there are helper classes for rules or statistics.
6. KI also is included in Logic via interface, so easy replacement is possible.
## How to play
### Dependencies
- GCC with g++ if use of provided MAKEFILE (and make then) is wanted
### Build the game
1. Load repository (main branch or one of the releases).
2. Run 'make' in 'Source'-directory. You can provide a path to which the executable ('maedn') should be build via 'make outpath=path/you/like' (tested on macos/ubuntu).
3. With 'make run' you can run a quick pre-configured game.

### Troubleshooting
If MAKEFILE is not working (maybe Windows):
- Use a c++ compiler (best will be GCC with g++) with language version 17.
- Compile and link all *.cpp files you find.
- This should do the same as the MAKEFILE

### Run the game
The settings of the game are selected by CL-argument or by configuration file. Once the game started you can not change settings but have to restart (You should never change rules of a game midway anyways...).
1. Configure game and run: This is done by command line arguments to the game executable. Following options
    - None: Pre-configured default game (not like 'make run'!): 4 Homes, 4 Players, 4 Pieces, Default rules
    - 6 or more (not counting the app itself): Starts an individual game. The six arguments are integers as followed in order. Everything after that are strings with players names.
        1. 4/6 - Number of Homes (Small or big board)
        2. 1-6 - Number of (human) players. Note: More players than homes won't work ;-)
        3. 3/4 - Number of game pieces per player
        4. 0-2 - RuleSet (0: Default; 1: Hard; 2: Easy)
        5. 0/1 - Fill remaining homes with KI-players (0: No; 1: Yes)
        6. 0/1 - Spread players on board (0: No; 1: Yes)(Only if not filled with KI and sensible to spread)
```plain
        Example:
        ./maedn 4 3 4
```
    - One: This must be a file in same directory (or a path). This must hold the same arguments like the 6 arguments, each in one line. Each name in a new line. With this you can have multiple configuration files to quickly start games. (See also sample file in 'Demo'-directory 'maedngame' for configuration only and 'maedngame1' for a save-file)
2. You can run via 'make run' a pre-configured game (4 Homes, 3 Players (Torsten, Niklas, Ingmar), 4 Pieces each, Default rules, Fill remaining homes with KI)
3. You can load a saved game with one CL-argument too: If you have exported a game state before, just take this file as CL-argument. It will hold game configuration and state.
4. If you are in the game you can exit the game and save the state if you wish. The saved file ('maedngame' or if already there with a number following will hold configuration and state of the game)
- See also in 'Demo'-directory for explanation of config/state-file
## Play
Well, everyone should know Mensch-ärgere-dich-nicht. If not, buy the real game or draw it on a paper and have fun getting annoyed by your fellow players. :D
In General:
- Goal of the game: Getting all of your game pieces from the home area into the target area. You walk on the field in direction of the clock.
1. You have to roll the dice (1-6)
2. You walk on the field (if you can not walk on the field you might roll again (depending on rules))
3. Next player (except you had a 6)
- For full explanation google for 'Mensch-ärgere-dich-nicht instructions'

## Rule Sets
This game offers 3 different rule sets you can choose from (Default, Easy and Hard). Use the number in brackets in the input arguments or the configuration file. Obviously it is possible that these rule sets differ from those you now as everyone play this game his own way. But while developing this game it became clear that its mostly luck, independent of the rules or strategy, who's winning, so just have fun with slight adjustments ;-)
Choose wisely!
Following an explanation to the different rule sets (each time all rules with True/False):
### General
If you have a 6 followed by another 6 you can not walk the second walk, except the easy rules.
### Default: Boring Default Rules (0 or else than 1/2)
- You must throw other pieces if you can (even if you have to walk by your target!): **False**
- You must throw your own pieces (only in special situations like if you are on the start field and have a 6 or if you are coming to the jumping field after going out of the home): **False**
- Throw also backwards: **False**
- Jump over your pieces in the target area: **False**
- Walk by the target area if you can not go in and have no other piece to walk: **False**
- You are save on startfields (Means there are multiple pieces possible on one field): **False**
- You always have to free the start field (Even if no pieces are left home): **False**
- You are allowed to go with another piece on the second roll when having a 6 (Overrides the rule before): **False**
- You only are allowed to roll three times if you have no pieces out AND all pieces in the target area are finished: **False**
- You must jump on the edges: **False**
- You are allowed to use an outside piece with a six (even if pieces are left home): **False**
- Game is finished when all players (including KI) have finished (Else finished when first player finished): **False**

### Hard: Only For The Real Players (1)
- You must throw other pieces if you can (even if you have to walk by your target!): **True**
- You must throw your own pieces (only in special situations like if you are on the start field and have a 6 or if you are coming to the jumping field after going out of the home): **True**
- Throw also backwards: **True**
- Jump over your pieces in the target area: **False**
- Walk by the target area if you can not go in and have no other piece to walk: **True**
- You are save on startfields (Means there are multiple pieces possible on one field): **False**
- You always have to free the start field (Even if no pieces are left home): **True**
- You are allowed to go with another piece on the second roll when having a 6 (Overrides the rule before): **False**
- You only are allowed to roll three times if you have no pieces out AND all pieces in the target area are finished: **True**
- You must jump on the edges: **True**
- You are allowed to use an outside piece with a six (even if pieces are left home): **False**
- Game is finished when all players (including KI) have finished (Else finished when first player finished): **True**

### Easy: For Wimps (Or Children) (2)
- You must throw other pieces if you can (even if you have to walk by your target!): **False**
- You must throw your own pieces (only in special situations like if you are on the start field and have a 6 or if you are coming to the jumping field after going out of the home): **False**
- Throw also backwards: **False**
- Jump over your pieces in the target area: **True**
- Walk by the target area if you can not go in and have no other piece to walk: **False**
- You are save on startfields (Means there are multiple pieces possible on one field): **True**
- You always have to free the start field (Even if no pieces are left home): **False**
- You are allowed to go with another piece on the second roll when having a 6 (Overrides the rule before): **True**
- You only are allowed to roll three times if you have no pieces out AND all pieces in the target area are finished: **False**
- You must jump on the edges: **False**
- You are allowed to use an outside piece with a six (even if pieces are left home): **True**
- Game is finished when all players (including KI) have finished (Else finished when first player finished): **False**
#### Clarification
On the start field multiple pieces are possible.
On the field if you would have to throw your own piece, you simply can not walk (except you have other free pieces).
## Contributors
- [Niklas Arnold](https://github.com/niklasar)
- [Ingmar Bauckhage](https://github.com/IngmarBuchenhain)

## License
[GPLv3 License](https://github.com/IngmarBuchenhain/Mensch-aergere-dich-nicht/blob/a9f37a3aa70579cdb452c9196e7cb0fd8359d22d/LICENSE)
