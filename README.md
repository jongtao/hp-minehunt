hp-minehunt
===========

A "port" of the minehunt easter egg from the HP-48 series calculators

The build was compiled on a 64-bit Debian machine. Run with ncurses library
installed.

You can build the game yourself from the makefile. Make sure you have the
ncurses development library installed to do this.


Gameplay
--------

Use the rogue keys (hjklyubn) to move around:
* h: left
* j: down
* k: up
* l: right
* y: up-left (diagonally)
* u: up-right
* b: down-left
* n: down-right

Use the escape key to quit at any time.

Navigate across a minefield to safety! Your minesweeping instincts will tell you
how many mines are "Near" you, which includes all the cardinal and ordinal
squares around you. Upon finishing a game, the game will display your score and
the seed.

The game can take the seed as an arguement, so it's possible to share a seed
amongst friends!
