#include <stdio.h>
#include "display.h"

void display_board(const Board *b){
    printf("\n  ");
    for(int c = 0; c < DOT_COLS; c++){
        printf("%d ", c);
    }
    printf("\n");

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