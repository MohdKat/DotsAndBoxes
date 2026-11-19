#include <stdio.h>
#include "display.h"

void display_board(const Board *b){
    printf("\n  ");
    for(int c = 0; c < DOT_COLS; c++){
        printf("%d ", c);
    }
    printf("\n");
// this is a comment to explain the logic of the display_board function. The function iterates through each row and column of the board, printing dots and lines based on the state of the board. It uses the h[][] array for horizontal lines and the v[][] array for vertical lines, as well as the owner[][] array to display which player owns each box. The function also prints the row and column indices for reference.
    for(int r = 0; r < DOT_ROWS; r++){
        //Printing the Dots and lines for the columns using the MACROS defined and h[][] for board b
        printf("%d ", r);
        for(int c = 0; c < DOT_COLS; c++){
            printf(".");
            if (c < BOX_COLS) {
                printf("%c", b->h[r][c] ? '-' : ' ');
            }
        }
        printf("\n");

        //filling the vertical lines for board b      
        if(r < BOX_ROWS){
            printf("  ");
            for(int c = 0; c < DOT_COLS; c++){
                printf("%c", b->v[r][c] ? '|' : ' ');
                if(c < BOX_COLS) {
                    printf("%c", b->owner[r][c]);
                }
            }
            printf("\n");
        }
    }
}

void display_scores(int score_a, int score_b){
    printf("Player A score: %d\n", score_a);
    printf("Player B score: %d\n", score_b);
    printf("********************************\n");
}