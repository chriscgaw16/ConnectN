#include <stdio.h>
#include <stdlib.h>
#include "setup_game.h"

/*
    Purpose: Initializes an empty board for a connectN game
    Input: Number of rows, Number of columns, and the amount of pieces in a row needed to win
    Output: Returns an empty board initialized with the inputs
*/

Board initialize_board(int num_of_rows, int num_of_cols, int pieces_needed_to_win){
    Board ret_board;

    ret_board.num_of_rows = num_of_rows;
    ret_board.num_of_cols = num_of_cols;
    ret_board.pieces_needed_to_win = pieces_needed_to_win;

    ret_board.amount_filled_in_each_column = (int*)calloc(num_of_cols, sizeof(int));

    ret_board.matrix = (char**)malloc(num_of_rows * sizeof(char*) + num_of_rows * num_of_cols * sizeof(char));
    char* ptr_to_data = (char*)(ret_board.matrix + num_of_rows);
    for(int i = 0; i < num_of_rows; i++){
        ret_board.matrix[i] = (ptr_to_data + num_of_cols * i);
        for(int j = 0; j < num_of_cols; j++){
            ret_board.matrix[i][j] = '*';
        }
    }

    return ret_board;
}

/*
    Purpose: Frees heap data used in Board b
    Input: Board as a struct
    Output: No return value
*/

void free_board(Board b){
    free(b.amount_filled_in_each_column);
    free(b.matrix);
}

/*
    Purpose: Parses a valid int from a specific command-line argument. Errors out if invalid not a positive integer
    Input: One command-line argument as string / char pointer
    Output: Returns integer or error depending if input it valid
*/

int get_valid_int(char* entry){
    int num = 0;
    char stuff = '\0';
    int num_args_read = sscanf(entry, "%d%c", &num, &stuff);
    if(num_args_read == 1 && num > 0){
        return num;
    }else{
        printf("Invalid arugments entered\n");
        printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win");
        exit(0);
    }
}

/*
    Purpose: Sets up the game board based on the command-line arguments entered. Errors out if invalid arguments are passed in
    Input: The number of arguments and arguments as string array
    Output: Initialized board based on inputs
*/

Board setup_game(int argc, char* argv[]){
    if(argc > 4){
        printf("Too many arguments entered\n");
        printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win");
        exit(0);
    }else if(argc < 4){
        printf("Not enough arguments entered\n");
        printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win");
        exit(0);
    }

    int num_of_rows = get_valid_int(argv[1]);
    int num_of_cols  = get_valid_int(argv[2]);
    int pieces_needed_to_win = get_valid_int(argv[3]);
    
    return initialize_board(num_of_rows, num_of_cols, pieces_needed_to_win);
}

/*
    Purpose: Displays the board on the terminal
    Input: The current board b
    Output: Nothing but prints out board in correct format in terminal
*/

void print_board(Board b){
    for(int i = b.num_of_rows - 1; i >= 0; i--){
        printf("%d ", i);
        for(int j = 0; j < b.num_of_cols; j++){
            printf("%c ", b.matrix[i][j]);
        }
        printf("\n");
    }
    printf("  ");
    for(int j = 0; j < b.num_of_cols; j++){
        printf("%d ", j);
    }
    printf("\n");
}
