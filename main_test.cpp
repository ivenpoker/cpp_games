//
// Created by deathshot on 3/8/18.
//

#include <iostream>
#include <cassert>
#include "TicTacToe_game/TicTacToe.h"
using namespace std;

int main(void) {
    int board_size = 0;

    cout << "Enter game board size: ";
    cin >> board_size;

    TicTacToe *game_board_1 = new TicTacToe(board_size);
    assert(game_board_1 != nullptr);

    int game_status = NO_WIN_FOR_PLAYER;
    int x_cord;
    int y_cord;

    do {
        game_board_1->dipslay_board();
        cout << endl;
        if (game_board_1->get_current_player() == TicTacToe::PLAYER_ONE) {
            cout << "\t\tMove for [X] as [x y]: ";
            cin >> x_cord >> y_cord;
            game_status = game_board_1->set_player_pos(TicTacToe::PLAYER_ONE, x_cord, y_cord);
        } else {
            cout << "\t\tMove for [O] as [x y]: ";
            cin >> x_cord >> y_cord;
            game_status = game_board_1->set_player_pos(TicTacToe::PLAYER_TWO, x_cord, y_cord);
        }
    } while (game_status == NO_WIN_FOR_PLAYER);

    if (game_status == PLAYER1_WINS) {
        game_board_1->dipslay_board();
        cout << endl << "\t\t[============== PLAYER 1 WINS =============]\n" << endl;

    } else if (game_status == PLAYER2_WINS) {
        game_board_1->dipslay_board();
        cout << endl << "\t\t[============== PLAYER 2 WINS =============]\n" << endl;
    }
    game_board_1->destroy_game();

    return EXIT_SUCCESS;
}