//
// Created by deathshot on 3/8/18.
//

#include <iostream>
#include "TicTacToe_game/TicTacToe.h"
using namespace std;

int main(void) {
    int board_size = 0;

    cout << "Enter games board size: ";
    cin >> board_size;

    TicTacToe *game_board = new TicTacToe(board_size);
    game_board->dipslay_board();

    return EXIT_SUCCESS;
}