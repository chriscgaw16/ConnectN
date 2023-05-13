#include <stdio.h>
#include "play_game.h"
#include "setup_game.h"


/*
    Purpose: Prints out appropriate statement based on how the game ended
    Input: Game state as an enum
    Output: No return value but prints how the game ended (Tie, Player 1 won, Player 2 won)
*/

void end_game(GAME_STATE game_end_state){
    switch(game_end_state){
        case TIE_GAME:
            printf("Tie game!");
        break;
        case PLAYER1_WON:
            printf("Player 1 Won!");
        break;
        case PLAYER2_WON:
            printf("Player 2 Won!");
        break;
        default:
            printf("Invalid game state passed into end_game");
        break;
    }
}

int main(int argc, char* argv[]){
    Board b = setup_game(argc, argv);
    GAME_STATE game_end_state = play_game(b);
    free_board(b);
    end_game(game_end_state);
}