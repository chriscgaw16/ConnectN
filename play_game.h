#ifndef PLAY_GAME_H
#define PLAY_GAME_H
#include "setup_game.h"
#include <stdbool.h>

bool isValidFormat(const int numArgsRead, const int numArgsNeed);
int getValidInt(const char* prompt);

typedef struct Iterator{
    int start_row;
    int start_column;
    int change_in_row;
    int change_in_column;
} Iterator;

char get_entry_in_board(Board b, int row_attempt, int col_attempt);
char get_n_in_line(Board b, Iterator line, int n);
bool has_player_won_in_line(Board b, Iterator line, int curr_player);

typedef enum GAME_STATE_DEF{
    PLAYER1_WON, PLAYER2_WON, TIE_GAME, GAME_HAS_NOT_ENDED
} GAME_STATE;

GAME_STATE determine_if_player_won(Board b, int player_number, int last_played_row, int last_played_column);
GAME_STATE determine_if_player_won(Board b, int player_number, int last_played_row, int last_played_column);
GAME_STATE determine_if_tied(Board b);
int get_valid_move(Board b);
int execute_valid_move(Board b, int column, int player_number);
char get_player_piece(int player_number);
int move_to_next_player(int curr_player_number);
GAME_STATE play_game(Board b);

#endif