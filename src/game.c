#include <stdio.h>
#include "game.h"
#include "board.h"
#include "display.h"
#include "input.h"

void run_game(void){
    //Create the board
    Board *b = board_create();
    if(b == NULL){
        fprintf(stderr, "Could not allocate the board.\n");
        return;
    }
    //Initialize the score array on stack
    int score[2] = {0, 0};
    char current = 'A';

    while(!board_is_full(b)){
        display_board(b);
        display_scores(score[0], score[1]);

        Move m = get_move(b, current);
        if (m.r1 == -1) { 
            printf("\nInput ended, game stopped.\n");
            break;
        }

        int won = board_apply_move(b, m, current);
        if(won > 0){
            //Increase the Player's score
            score[current - 'A'] += won;
        }else{
            current = (current == 'A') ? 'B' : 'A';
        }
    }

    display_board(b);
    display_scores(score[0], score[1]);
    if(board_is_full(b)){
        if(score[0] > score[1]){
            printf("Player A wins!\n");
        } else if(score[1] > score[0]){
            printf("Player B wins!\n");
        }else{
            printf("It's a draw!\n");
        }
    }

    board_destroy(b);
}