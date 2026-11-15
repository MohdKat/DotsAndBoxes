#include <stdio.h>
#include "board.h"

/* Temporary test driver for board.c, replaced by run_game() later */
static void play(Board *b, int r1, int c1, int r2, int c2, char player)
{
    Move m = {r1, c1, r2, c2};
    if (!board_is_valid_move(b, m)) {
        printf("%c: %d %d %d %d -> invalid\n", player, r1, c1, r2, c2);
        return;
    }
    int won = board_apply_move(b, m, player);
    printf("%c: %d %d %d %d -> valid, won %d\n", player, r1, c1, r2, c2, won);
}

int main(void)
{
    Board *b = board_create();
    if (b == NULL) {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }

    /* the 4 sides of box (0,0): B draws the last one and wins it */
    play(b, 0, 0, 0, 1, 'A');   /* top    */
    play(b, 1, 0, 1, 1, 'B');   /* bottom */
    play(b, 0, 0, 1, 0, 'A');   /* left   */
    play(b, 0, 1, 1, 1, 'B');   /* right  */

    /* must all be rejected */
    play(b, 0, 0, 0, 1, 'A');   /* already drawn */
    play(b, 0, 0, 1, 1, 'A');   /* diagonal      */
    play(b, 0, 0, 0, 2, 'A');   /* too long      */
    play(b, 4, 5, 4, 6, 'A');   /* off the board */

    /* edge lines: only one box each */
    play(b, 4, 4, 4, 5, 'A');   /* bottom edge */
    play(b, 3, 5, 4, 5, 'A');   /* right edge  */

    /* draw every remaining line: board must end full */
    for (int r = 0; r < DOT_ROWS; r++) {
        for (int c = 0; c + 1 < DOT_COLS; c++) {
            Move m = {r, c, r, c + 1};
            if (board_is_valid_move(b, m)) board_apply_move(b, m, 'A');
        }
    }
    for (int r = 0; r + 1 < DOT_ROWS; r++) {
        for (int c = 0; c < DOT_COLS; c++) {
            Move m = {r, c, r + 1, c};
            if (board_is_valid_move(b, m)) board_apply_move(b, m, 'A');
        }
    }

    printf("owner of box (0,0): '%c'\n", b->owner[0][0]);
    printf("claimed: %d, full: %d\n", b->claimed, board_is_full(b));

    board_destroy(b);
    return 0;
}