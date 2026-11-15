
#include <stdio.h>
#include <assert.h>
#include "board.h"

void test_board_creation(void)
{
    Board *b = board_create();

    assert(b != NULL);
    assert(b->claimed == 0);
    assert(b->owner[0][0] == ' ');
    assert(board_is_full(b) == 0);

    board_destroy(b);
    printf("Board creation: PASSED\n");
}

void test_valid_moves(void)
{
    Board *b = board_create();

    Move valid = {0, 0, 0, 1};
    Move diagonal = {0, 0, 1, 1};
    Move out_of_bounds = {-1, 0, 0, 0};

    assert(board_is_valid_move(b, valid) == 1);
    assert(board_is_valid_move(b, diagonal) == 0);
    assert(board_is_valid_move(b, out_of_bounds) == 0);

    board_destroy(b);
    printf("Move validation: PASSED\n");
}

void test_duplicate_move(void)
{
    Board *b = board_create();
    Move m = {0, 0, 0, 1};

    assert(board_is_valid_move(b, m) == 1);

    board_apply_move(b, m, 'A');

    assert(board_is_valid_move(b, m) == 0);

    board_destroy(b);
    printf("Duplicate move prevention: PASSED\n");
}

void test_box_completion(void)
{
    Board *b = board_create();

    Move moves[] = {
        {0, 0, 0, 1},
        {1, 0, 1, 1},
        {0, 0, 1, 0},
        {0, 1, 1, 1}
    };

    for (int i = 0; i < 3; i++) {
        assert(board_is_valid_move(b, moves[i]));
        assert(board_apply_move(b, moves[i], 'A') == 0);
    }

    assert(board_is_valid_move(b, moves[3]));
    assert(board_apply_move(b, moves[3], 'A') == 1);

    assert(b->owner[0][0] == 'A');
    assert(b->claimed == 1);

    board_destroy(b);
    printf("Box completion and scoring: PASSED\n");
}

void test_full_board(void)
{
    Board *b = board_create();

    for (int r = 0; r < DOT_ROWS; r++) {
        for (int c = 0; c < BOX_COLS; c++) {
            Move m = {r, c, r, c + 1};

            assert(board_is_valid_move(b, m));
            board_apply_move(b, m, 'A');
        }
    }

    for (int r = 0; r < BOX_ROWS; r++) {
        for (int c = 0; c < DOT_COLS; c++) {
            Move m = {r, c, r + 1, c};

            assert(board_is_valid_move(b, m));
            board_apply_move(b, m, 'A');
        }
    }

    assert(board_is_full(b) == 1);
    assert(b->claimed == TOTAL_BOXES);

    board_destroy(b);
    printf("Full board detection: PASSED\n");
}

int main(void)
{
    test_board_creation();
    test_valid_moves();
    test_duplicate_move();
    test_box_completion();
    test_full_board();

    printf("\nAll tests passed!\n");

    return 0;
}
