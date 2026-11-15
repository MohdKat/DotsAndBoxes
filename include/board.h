#ifndef BOARD_H
#define BOARD_H

#define BOX_ROWS 4
#define BOX_COLS 5
#define DOT_ROWS (BOX_ROWS + 1)            /* 5 */
#define DOT_COLS (BOX_COLS + 1)            /* 6 */
#define TOTAL_BOXES (BOX_ROWS * BOX_COLS)  /* 20 */

typedef struct {
    //Vertical move
    int  h[DOT_ROWS][BOX_COLS];
    //Horizontal move
    int  v[BOX_ROWS][DOT_COLS];
    //box states
    int  sides[BOX_ROWS][BOX_COLS];
    //Identifies who won each box
    char owner[BOX_ROWS][BOX_COLS];
    //Status of each box
    int  claimed;
} Board;

typedef struct {
    //Created from input from user
    int r1, c1, r2, c2;
} Move;

Board *board_create(void);
void   board_destroy(Board *b);
//Checks for the validity of the player's move
int    board_is_valid_move(const Board *b, Move m);
//If move if valid call box_apply_move to draw the line
int    board_apply_move(Board *b, Move m, char player);
int    board_is_full(const Board *b);

#endif  
