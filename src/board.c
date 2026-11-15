#include <stdlib.h>   /* calloc, free, abs */
#include "board.h"

Board *board_create(void)
{
    //callocing the Board we need to access it from other files, having it present in the process heap
    //Why calloc not malloc? TO initialize the bytes of the board to 0s
    Board *b = calloc(1, sizeof(Board));
    if (b == NULL) {
        perror("Could not successfully allocate heap memory!");
        return NULL;
    }
    for (int r = 0; r < BOX_ROWS; r++) {
        for (int c = 0; c < BOX_COLS; c++) {
            b->owner[r][c] = ' ';
        }
    }
    return b;
}

void board_destroy(Board *b)
{
    //Destroy B from heap
    free(b);
}

//internal linkage for this function we need it to be exclusively used by board.c because it changes the board itself
static void add_side(Board *b, int r, int c, char player, int *won)
{
    b->sides[r][c]++;
    if (b->sides[r][c] == 4) {
        b->owner[r][c] = player;
        b->claimed++;
        (*won)++;
    }
}

int board_is_valid_move(const Board *b, Move m)
{
    //Checks if dots are calid and on the board
    if (m.r1 < 0 || m.r1 >= DOT_ROWS || m.r2 < 0 || m.r2 >= DOT_ROWS ||
        m.c1 < 0 || m.c1 >= DOT_COLS || m.c2 < 0 || m.c2 >= DOT_COLS) {
        return 0;
    }

    //Valid horizontal move and vertical move no diagonal moves
    int horizontal = (m.r1 == m.r2 && abs(m.c1 - m.c2) == 1);
    int vertical   = (m.c1 == m.c2 && abs(m.r1 - m.r2) == 1);
    if (!horizontal && !vertical) {
        return 0;
    }

    //Checks if lines are already drawn to check if the move is permitted
    if (horizontal) {
        int c = (m.c1 < m.c2) ? m.c1 : m.c2;
        return b->h[m.r1][c] == 0;
    } else {
        int r = (m.r1 < m.r2) ? m.r1 : m.r2;
        return b->v[r][m.c1] == 0;
    }
}

int board_apply_move(Board *b, Move m, char player)
{
    int won = 0;
    //Horizontal line
    if (m.r1 == m.r2) {
        int r = m.r1;
        int c = (m.c1 < m.c2) ? m.c1 : m.c2;
        b->h[r][c] = 1;
        if (r > 0)        add_side(b, r - 1, c, player, &won);
        if (r < BOX_ROWS) add_side(b, r,     c, player, &won); //Box under
    } else {  //Vertical line
        int c = m.c1;
        int r = (m.r1 < m.r2) ? m.r1 : m.r2;
        b->v[r][c] = 1;
        if (c > 0)        add_side(b, r, c - 1, player, &won);  //Accpunting for left box
        if (c < BOX_COLS) add_side(b, r, c,     player, &won);  //Accounting for right box
    }
    return won;
}

int board_is_full(const Board *b)
{
    return b->claimed == TOTAL_BOXES;
}