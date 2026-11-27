
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "tinymt32.h"

tinymt32_t state;
uint32_t pseudo_seed = 0;
int K;


void generate_new_board (int board[100]);
void print_board (int board[100]);
int elim_matches (int board[100]);
void drop_numbers (int board[100]);
void fill_empty_spots (int board[100]);
void initialize_board (int board[100]);

int
main (void) {

    int board[100] = {0};
    // int num_swaps = 0;
    // int total_score = 0;

    scanf("%d", &K);

    scanf("%u", &pseudo_seed);
    tinymt32_init(&state, pseudo_seed);


    // int random_int = tinymt32_generate_uint32(&state) % K + 1;
    // printf("%d", random_int);

    printf("==============\n");
    initialize_board(board);

    return 0;
}


void generate_new_board (int board[100]) {

    for (int i = 0; i < 100; i++) {
        if (board[i] == 0) {
            board[i] = tinymt32_generate_uint32(&state) % K + 1;
        }
    }

}

void print_board (int board[100]) {
    printf("    0 1 2 3 4 5 6 7 8 9\n");
    printf("   --------------------\n");

    for (int i = 0; i < 100; i += 10) {
        printf("%d | ", i / 10);

        for (int j = 0; j < 10; j++) {
            printf("%d ", board[i+j]);
        }

        printf("\n");
    }
}

int elim_matches (int board[100]) {
    int to_clear[100] = {0};
    int isElim = 0;


    // for each cell
    for (int i = 0; i < 100; i++) {
        int curr_num = board[i];

        if (curr_num == 0) continue;

        // for cells left to right till last[i/10 + 9]
        if (i % 10 == 0 || board[i-1] != curr_num) {
            int match_count_H = 1;
            int row_end = (i/10)*10 + 9;

            for (int j = i+1; j <= row_end; j++) {
                if (board[j] == curr_num) {
                    match_count_H++;
                }
                else {
                    break;
                }
            }


            if (match_count_H >= 3) {
                // set match to zero
                if (match_count_H >= 5) {
                    int row_start = (i / 10) * 10;
                    for (int j = row_start; j <= row_start+9; j++) {
                        to_clear[j] = 1;
                    }
                }
                else {
                    for (int j = i; j < i + match_count_H; j++) {
                        to_clear[j] = 1;
                    }
                }
                // calc_score(match_count_H, total_score);
            }

        }


        // for cells top to bottom till last[90], each next is i+10
        if (i < 10 || board[i-10] != curr_num) {
            int match_count_V = 1;

            for (int j = i+10; j <= 99; j += 10) {
                if (board[j] == curr_num) {
                    match_count_V++;
                }
                else {
                    break;
                }
            }


            if (match_count_V >= 3) {
                // set match to zero
                if (match_count_V >= 5) {
                    for (int r = 0; r < 10; r++) {
                        to_clear[r*10 + (i%10)] = 1;
                    }
                }
                else {
                    for (int j = i; j < i + match_count_V*10; j += 10) {
                        to_clear[j] = 1;
                    }
                }
                // calc_score(match_count_V, total_score);
            }
        }

    }


    // clear board values from to_clear
    for (int i = 0; i < 100; i++) {
        if (to_clear[i] == 1) {
            board[i] = 0;
            isElim = 1;
        }
    }

    if (!isElim) {
        return 0;
    }
    else {
        return 1;
    }
}

void drop_numbers (int board[100]) {

    // for each cell, starting from last to first
    // for (int i = 99; i >= 0; i--) {
    //
    //     if (board[i] == 0) {
    //
    //         int curr_pos = i;
    //
    //         while (curr_pos > 9) {
    //             board[curr_pos] = board[curr_pos - 10];
    //             curr_pos -= 10;
    //         }
    //
    //         if (curr_pos < 10) {
    //             board[curr_pos] = 0;
    //         }
    //     }
    //
    // }

    // for each col
    for (int col = 0; col <= 9; col++) {
        int start_from = 9;

        // for each row, from bottom
        for (int row = 9; row >= 0; row--) {
            int index = row * 10 + col;

            if (board[index] != 0) {
                board[start_from * 10 + col] = board[index];
                start_from--;
            }
        }

        // fill all the rest
        for (int i = start_from; i >= 0; i--) {
            board[i * 10 + col] = 0;
        }
    }

    printf("Drop numbers down\n");
    print_board(board);

}

void fill_empty_spots (int board[100]) {
    // for each row, top to bottom
    for (int i = 0; i < 100; i += 10) {

        // for each col, left to right
        for (int j = 0; j < 10; j++) {

            if (board[i+j] == 0) {
                board[i+j] = tinymt32_generate_uint32(&state) % K + 1;
            }
        }
    }

    // printf("Fill empty spots\n");
    // print_board(board);
}

void elim_all_matches (int board[100]) {

    while (elim_matches(board) == 1) {
        // elim_matches(board);
        drop_numbers(board);
        fill_empty_spots(board);
        // printf("elim_all matches call done\n");
    }
}

void initialize_board (int board[100]) {

    generate_new_board(board);
    // printf("inital board\n");
    // print_board(board);

    // printf("==========================\n");

    // elim_matches(board);
    // print_board(board);
    //
    // printf("==========================\n");
    //
    // drop_numbers(board);
    // print_board(board);
    //
    // printf("==========================\n");
    //
    // fill_empty_spots(board);
    // print_board(board);

    elim_all_matches(board);
    print_board(board);
}

