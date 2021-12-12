# How to contribute
This is a studies project, so there might be mistakes, bad patterns or other unconventional stuff.
Feel free to open an Issue to point it out, so we can learn.
This ReadMe covers some ideas for the development of this app with git/github, "design pattern" and file structure.

## Ideas on "design pattern"
From the entry point of the application 2 to 4 objects are created.
- UI-object (IUI)
- Logic-object ()
- {optional} Network-object () // Planned for future
- {optional} KI-object ()      // Planed for future

Logic-object will receive other objects in constructor.

Logic-object is responsible for "application-cycle". Here
1. UI-object will be used to present something to user or have interaction.
2. Rolling dices will be simulated.
3. Data hold by Logic-object will be manipulated.
4. Network-object will be used to communicate with others.
5. KI-object will be used to determine game piece to walt if KI-players are included.

For easier development there is an interface for UI (IUI) so UI can be developed independent. IUI must know therefore the data it has to present. (..)

## File-Structure
All source files are in the directory 'Source'.
There is also a "Makefile" to build and run the project. (Only tested on macos)
In this top directory only the starting point of the application is stored. Also some source used for debug helping.
The rest of source is split into
- Interfaces
- Logic
- Model
- Networking
- UI

Right now the Makefile is not ready for use with this filestructure. 
You can use own temporary Makefiles in the sub-directories.

## Git/Github and Branches
The main branch ALWAYS should be in good state. 
For developing features use a new branch. If finished with work and testing make a pull-request to main.
Some branches are already there to be used. We will most likely need no more branches.