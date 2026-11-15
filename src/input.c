#include <stdio.h>
#include "input.h"

Move get_move(const Board *b, char player)
{
    Move m;
    int ch;

    while (1) {
        printf("\nPlayer %c, enter your move (r1 c1 r2 c2): ", player);
        fflush(stdout);

        if (scanf("%d %d %d %d",
                  &m.r1, &m.c1, &m.r2, &m.c2) != 4) {

            printf("Invalid input. Enter four integers.\n");

            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            continue;
        }

        if (!board_is_valid_move(b, m)) {
            printf("Invalid move. Try again.\n");
            continue;
        }

        return m;
    }
}