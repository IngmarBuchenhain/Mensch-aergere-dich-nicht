# Mensch-aergere-dich-nicht
This is a simple board game most people know which can be played by CLI.
## How to get it
### Dependencies
- boost library (version 1.78.0 was used for development)
- GCC if use of provided MAKEFILE is wanted
### Build the game
1. Load repository
2. Run 'make' in 'Source'-directory with boost paths as arguments as follows: make boost=path/to/your/boost boostLib=path/to/your/boost/libs
## Rule Sets
This game offers 3 different rule sets you can choose from. Use the number in brackets in the input arguments or the configuration file.
Choose wisely!
### General rules
Apply for all rule sets.
- If no piece is on the field you are allowed to roll the dice 3 times until you get a 6.
### Boring Default Rules (0)
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
### For Wimps (1)
### Only For The Real Players (2)
Must-Throw other pieces: Yes
Must-Throw own pieces (only if no other possibility): Yes
Throw also backwards: Yes
Jump over pieces in "home"-row: No
Throwable on "Start"-Field: Yes
## License
[GPLv3 License](https://github.com/IngmarBuchenhain/Mensch-aergere-dich-nicht/blob/a9f37a3aa70579cdb452c9196e7cb0fd8359d22d/LICENSE)
