# cc3k
A fun dungeon crawler written in C++

Download the files in the code folder and use the make command to compile the game. You have to have a c++ complier installed in order to make it work. 
A UML diagram is avaiable as well, titled UML.pdf

The demo file describes a list of all the features implemented, with instructions on how to explore them. Alternatively, feel free to explore the game without guidance with the command "./cc3k"

Commands: 
The following commands can be supplied to your command interpreter:
- no,so,ea,we,ne,nw,se,sw: moves the player character one block in the appropriate cardinal direction.
- u <direction>: uses the potion indicated by the direction (e.g. no, so, ea).
- a <direction>: attacks the enemy in the specified direction, if the monster is in the immediately
specified block (e.g. must be one block north of the @).
- s, d, v, g, t: specifies the race the player wishes to be when starting a game.
- f: stops enemies from moving until this key is pressed again.
- r: restarts the game. All stats, inventory, and gold are reset. A new race should be selected.
- q: allows the player to admit defeat and exit the game.
