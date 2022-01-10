# How to contribute
This is a studies project, so there might be mistakes, bad patterns or other unconventional stuff.
Feel free to open an issue to point it out, so we can learn.
This ReadMe covers some ideas for the development of this app with git/github, "design pattern" and file structure, so everyone is familiar and there is no trouble in working together.

## Ideas on "design pattern"
The entry point of the application provides different ways:
- No arguments
- One argument: A file which holds configuration of the game or configuration with state of a saved game
- Six or more arguments: The game configuration directly

From the entry point of the application 2 objects are created:
- UI-object (IUI)
- Logic-object (MainLogicBase) Depending on the rules a specialized class of MainLogicBase is used to implement the different rules.

Logic-object will receive UI-object in constructor along with configuration.

Logic-object is responsible for "application-cycle". Here
1. UI-object will be used to present something to user or have interaction.
2. Rolling dices will be simulated.
3. Data hold by Logic-object will be manipulated.
5. KI-object will be used to determine game piece to walk if KI-players are included.

For easier development there is an interface for UI (IUI) so UI can be developed independent. IUI must know therefore the data it has to present.

## File-Structure
All source files are in the directory 'Source'.
There is also a "Makefile" to build and run the project. (Only tested on macos right now)
In this top directory only the starting point of the application along with debug helper and export/import helper is stored.
The rest of source is split into
- Interfaces
- Logic
- Model
- UI

## Git/Github and Branches
The main branch ALWAYS must be in good state (Compiling). 
For developing features use a new branch. If finished with work and testing make a pull-request to main.