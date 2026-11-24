
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "tinymt32.h"

tinymt32_t state;
uint32_t pseudo_seed = 0;
int K;


void generate_new_numbers (int board[100]);
void print_board (int board[100]);
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


void generate_new_numbers (int board[100]) {

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


void initialize_board (int board[100]) {

    generate_new_numbers(board);

    print_board(board);
}

