#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "play_game.h"

/*
    Purpose: Clears buffer and determines if format is valid
    Input: Number of arguments read and the number of arguments needed
    Output: Returns boolean indicating if input is valid
*/

bool isValidFormat(const int numArgsRead, const int numArgsNeed) {
  bool formatIsGood = numArgsRead == numArgsNeed;
  char character;
  do{
    scanf("%c", &character); //45  bob  \n
		if(!isspace(character)){ //found a non whitespace character on the way to the end of the line
			formatIsGood = false;
		}
	}while(character != '\n'); //read characters until the end of the line
  return formatIsGood;
}

/*
    Purpose: To get a valid integer input from the user
    Input: Prompt as string or char*
    Output: Returns the valid integer input from the user
*/

int getValidInt(const char* prompt){
  int num;
  const int numArgsNeeded = 1;
  int numArgsRead;
  do{
    printf("%s", prompt);
    numArgsRead = scanf(" %d", &num); // waffles 45\n
  }while(!isValidFormat(numArgsRead, numArgsNeeded));

  return num;
}

/*
    Purpose: To change the current player to move to the next turn
    Input: The current player number
    Output: Returns the next player's number that will play
*/

int move_to_next_player(int curr_player_number){
    if(curr_player_number == 1){
        return 2;
    }else if(curr_player_number == 2){
        return 1;
    }else{
        printf("Something went wrong with move to next player. Current player number entered was %d", curr_player_number);
        exit(0);
    }
}

/*
    Purpose: Get the player's designated piece based on the player's number
    Input: The player number
    Output: Returns char representing character's piece ('X' for 1 and 'O' for 2)
*/

char get_player_piece(int player_number){
    if(player_number == 1){
        return 'X';
    }else if(player_number == 2){
        return 'O';
    }else{
        printf("Something went wrong with get player piece. Player number entered was %d", player_number);
        exit(0);
    }
}

/*
    Purpose: Get a valid column to make a move from the player
    Input: The current board
    Output: Returns the column of the valid move from the player
*/

int get_valid_move(Board b){
    int column_to_be_played;
    char prompt[50];
    sprintf(prompt, "Enter a column between %d and %d to play in: ", 0, b.num_of_cols - 1);
    do{
        column_to_be_played = getValidInt(prompt);
    }while(!(column_to_be_played >= 0 && column_to_be_played < b.num_of_cols && b.amount_filled_in_each_column[column_to_be_played] < b.num_of_rows));
    return column_to_be_played;
}

/*
    Purpose: Executes the valid move and updates the board. Assumes the inputs are valid
    Input: The board, column the move was made in and the current player
    Output: Returns row where valid piece was placed
*/

int execute_valid_move(Board b, int column, int player_number){
    int next_avaliable_tile = b.amount_filled_in_each_column[column];
    b.matrix[next_avaliable_tile][column] = get_player_piece(player_number);
    b.amount_filled_in_each_column[column]++;
    return b.amount_filled_in_each_column[column] - 1;
}

/*
    Purpose: Determines if the board is in a tied state
    Input: The board as a struct
    Output: Returns the game state of the board
*/

GAME_STATE determine_if_tied(Board b){
    for(int i = 0; i < b.num_of_cols; i++){
        if(b.amount_filled_in_each_column[i] < b.num_of_rows){
            return GAME_HAS_NOT_ENDED;
        }
    }
    return TIE_GAME;
}

/*
    Purpose: Gets a tile in the board. Returns null character if tile is out of the board bounds
    Input: The board, the row of the attempted access, the column of the attempted access
    Output: Returns the char in the tile or the null character if the tile is out of bounds
*/

char get_entry_in_board(Board b, int row_attempt, int col_attempt){
    if(row_attempt < b.num_of_rows && col_attempt < b.num_of_cols && row_attempt >= 0 && col_attempt >= 0){
        return b.matrix[row_attempt][col_attempt];
    }else{
        return '\0';
    }
}

/*
    Purpose: Gets the nth character in the iterator line (row, column, diagonal, etc.) based on board b 
    Input: The board, The line as an iterator, and n as the nth place in line to access
    Output: Returns the char in the nth entry of the line or the null character if it is invalid
*/

char get_n_in_line(Board b, Iterator line, int n){
    int row_attempt = line.start_row + line.change_in_row * n;
    int col_attempt = line.start_column + line.change_in_column * n;
    return get_entry_in_board(b, row_attempt, col_attempt);
}

/*
    Purpose: Returns if the player has won in a specific line in the board
    Input: The board, The line as an iterator, and the current player who played the last piece
    Output: Returns if the current player has won in that specific line (row, column, diagonal, etc.)
*/

bool has_player_won_in_line(Board b, Iterator line, int curr_player){
    char curr_player_piece = get_player_piece(curr_player);
    int need_to_win = b.pieces_needed_to_win;
    int count = 0;
    int length = (2 * (need_to_win - 1)) + 1;
    for(int i = 0; i < length; i++){
        if(get_n_in_line(b, line, i) == curr_player_piece){
            count++;
            if(count == need_to_win){
                return true;
            }
        }else{
            count = 0;
        }
    }
    return false;
}

/*
    Purpose: Determine if the player has won the game
    Input: The board, the player's number, the column of the last played piece, and the row of the last played piece
    Output: Returns the Game state of the board
*/

GAME_STATE determine_if_player_won(Board b, int player_number, int last_played_row, int last_played_column){
    int amount_diff = b.pieces_needed_to_win - 1;
    Iterator row = {last_played_row - amount_diff, last_played_column, 1, 0};
    Iterator column = {last_played_row, last_played_column  - amount_diff, 0, 1};
    Iterator left_diagonal = {last_played_row + amount_diff , last_played_column - amount_diff, -1, 1};
    Iterator right_diagonal = {last_played_row - amount_diff, last_played_column - amount_diff, 1, 1};

    bool row_win = has_player_won_in_line(b, row, player_number);
    bool column_win = has_player_won_in_line(b, column, player_number);
    bool left_diagonal_win = has_player_won_in_line(b, left_diagonal, player_number);
    bool right_diagonal_win = has_player_won_in_line(b, right_diagonal, player_number);

    if(row_win || column_win || left_diagonal_win || right_diagonal_win){
        if(player_number == 1){
            return PLAYER1_WON;
        }else if(player_number == 2){
            return PLAYER2_WON;
        }else{
            printf("Something went wrong in determine_if_player_won");
            exit(0);
        }
    }else{
        return GAME_HAS_NOT_ENDED;
    }
}

/*
    Purpose: Determines if the game has ended and returns the corresponding GAME_STATE
    Input: The board, the player's number, the column of the last played piece, and the row of the last played piece
    Output: Returns the game state of the board
*/

GAME_STATE determined_if_game_has_ended(Board b, int player_number, int last_played_row, int last_played_column){
    GAME_STATE player_has_won = determine_if_player_won(b, player_number, last_played_row, last_played_column);
    GAME_STATE game_tied = determine_if_tied(b);
    if(player_has_won != GAME_HAS_NOT_ENDED){
        return player_has_won;
    }
    if(game_tied != GAME_HAS_NOT_ENDED){
        return game_tied;
    }
    return GAME_HAS_NOT_ENDED;
}

/*
    Purpose: Plays the game given an initialized board
    Input: The initialized board
    Output: Returns the ended game state of the board
*/

GAME_STATE play_game(Board b){
    print_board(b);
    int curr_player_number = 1;
    GAME_STATE curr_game_state = GAME_HAS_NOT_ENDED;
    do{
        int curr_column = get_valid_move(b);
        int curr_row = execute_valid_move(b, curr_column, curr_player_number);
        print_board(b);
        curr_game_state = determined_if_game_has_ended(b, curr_player_number, curr_row, curr_column);
        curr_player_number = move_to_next_player(curr_player_number);
    }while(curr_game_state == GAME_HAS_NOT_ENDED);
    return curr_game_state;
}