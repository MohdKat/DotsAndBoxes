#ifndef INPUT_H
#define INPUT_H

#include "board.h"

//Keeps asking until the player enters a valid move: correct coordinates and the whole shebang...
Move get_move(const Board *b, char player);

#endif