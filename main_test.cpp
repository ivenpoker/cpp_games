//
// Created by deathshot on 3/8/18.
//

#include <iostream>
#include "TicTacToe_game/TicTacToe.h"
using namespace std;

int main(void) {
    int board_size = 0;

    cout << "Enter game board size: ";
    cin >> board_size;

    TicTacToe *game_board_1 = new TicTacToe(board_size);
    game_board_1->set_player_pos(TicTacToe::PLAYER_ONE, 0, 2);
    game_board_1->set_player_pos(TicTacToe::PLAYER_TWO, 1, 1);


    game_board_1->dipslay_board();

    return EXIT_SUCCESS;
}