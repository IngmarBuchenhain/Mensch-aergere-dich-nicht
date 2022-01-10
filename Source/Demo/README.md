# Explanation of save-game-file
The following enumeration represent the lines of the save-game-file and the explanation
1. Number of homes (4/6)
2. Number of players (1-6)
3. Number of game pieces per player (3/4)
4. RuleSet (0-2)
5. Option to fill with KI if wanted (0/1)
6. Option to spread players on board if wanted and necessary (0/1)
7. - 12. Name of players. If less players than 6 make an empty line. You can also make names for the KI-players here if wanted. Just fill up to 6 names here. The human players get the first, the KI the remaining. You can also keep all lines here empty, than the game will assign names.
13. Indicator whether this is a saved game or only configuration (1: This is a save-game - Load the state; Else: Only take the configuration)
14. Dice rolls of number 1
15. Dice rolls of number 2
16. - 19. Remaining dice numbers
20. Current player
21. ID of last game piece (This is needed if a player had a six and has to go with same piece again)
22. Number of following game pieces
23. and following: Information about every game piece
    23.1 ID
    23.2 position
    23.3 target area or not
    23.4 finished