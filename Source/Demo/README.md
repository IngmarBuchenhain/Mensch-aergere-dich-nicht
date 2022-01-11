# Explanation of save-game-file
The following enumeration represent the lines of the save-game-file and the explanation
1. Number of homes (4/6)
2. Number of players (1-6)
3. Number of game pieces per player (3/4)
4. RuleSet (0-2)
5. Option to fill with KI if wanted (0/1)
6. Option to spread players on board if wanted and necessary (0/1)
7. to 12 - Name of players. If less players than 6 make an empty line. You can also keep all lines here empty, than the game will assign names.
8.
9.
10.
11.
12.
13. Indicator whether this is a saved game or only configuration (1: This is a save-game - Load the state; Else number: Only take the configuration)
14. Dice rolls of number 1
15. Dice rolls of number 2
16. to 19 - Remaining dice numbers
17.
18.
19.
20. Current player
21. ID of last game piece (This is needed if a player had a six and has to go with same piece again)
22. Number of following game pieces
23. and following: Information about every game piece. 4 lines each piece: ID on line 23
24. position
25. target area or not
26. finished