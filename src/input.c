#include <stdio.h>
#include <string.h>
#include "input.h"

Move get_move(const Board *b, char player){
    char line[64];
    Move m;

    while(1){
        printf("Player %c's turn. Enter the row and column of the first dot and second dot (e.g. 0 0 0 1): ", player);
        //Empties the buffer into stdout for us to get the Move
        fflush(stdout);

        //No move entered
        if (fgets(line, sizeof line, stdin) == NULL) {
            Move quit = {-1, -1, -1, -1};
            return quit;
        }

        //Line is longer than the buffer
        if (strchr(line, '\n') == NULL) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
        }

        //Scans for Move and validates the move
        if (sscanf(line, "%d %d %d %d", &m.r1, &m.c1, &m.r2, &m.c2) == 4 && board_is_valid_move(b, m)) {
            return m;
        }
        printf("Invalid move, try again.\n");
    }
}