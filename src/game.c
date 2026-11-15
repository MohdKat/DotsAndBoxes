#include <stdio.h>
#include "board.h"
#include "display.h"
#include "input.h"
#include "game.h"

void run_game(void)
{
    Board *b = board_create();

    if (b == NULL) {
        printf("Error: Could not create the game board.\n");
        return;
    }

    int score_a = 0;
    int score_b = 0;
    char current_player = 'A';

    printf("\n========== DOTS AND BOXES ==========\n");
    printf("Board size: %d x %d boxes\n", BOX_ROWS, BOX_COLS);
    printf("Enter moves as: r1 c1 r2 c2\n");
    printf("Coordinates start at 0.\n");

    display_board(b);
    display_scores(score_a, score_b);

    while (!board_is_full(b)) {
        Move m = get_move(b, current_player);
        if (m.r1 == -1) {
             printf("\nInput ended. Exiting game.\n");
             board_destroy(b);
             return;
            }
        
        int boxes_won = board_apply_move(b, m, current_player);

        if (current_player == 'A') {
            score_a += boxes_won;
        } else {
            score_b += boxes_won;
        }

        display_board(b);
        display_scores(score_a, score_b);

        if (boxes_won == 0) {
            current_player = (current_player == 'A') ? 'B' : 'A';
        }
    }

    printf("\n========== GAME OVER ==========\n");

    if (score_a > score_b) {
        printf("Player A wins!\n");
    } else if (score_b > score_a) {
        printf("Player B wins!\n");
    } else {
        printf("It's a draw!\n");
    }

    printf("Final score: A = %d | B = %d\n", score_a, score_b);

    board_destroy(b);
}