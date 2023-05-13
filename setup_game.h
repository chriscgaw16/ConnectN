#ifndef SETUP_GAME_H
#define SETUP_GAME_H

typedef struct Board{
    char** matrix;
    int num_of_rows;
    int num_of_cols;
    int* amount_filled_in_each_column;
    int pieces_needed_to_win;
} Board;

Board initialize_board(int num_of_rows, int num_of_cols, int pieces_needed_to_win);
int get_valid_int(char* entry);
Board setup_game(int argc, char* argv[]);
void free_board(Board b);
void print_board(Board b);

#endif