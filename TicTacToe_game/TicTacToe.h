//
// Created by deathshot on 3/8/18.
//

#ifndef CPP_GAMES_TIC_TAC_TOE_H
#define CPP_GAMES_TIC_TAC_TOE_H

#define INVALID_BOARD_SIZE      (0)
#define INVALID_PLAYER_MOVE     (1)
#define PLAYER1_WINS            (2)
#define PLAYER2_WINS            (3)
#define PLAYER1_TURN            (4)
#define PLAYER2_TURN            (5)
#define CANNOT_MAKE_MOVE        (6)
#define INVALID_BOARD_STATE     (7)


#include <iostream>
#include <vector>
using namespace std;


class TicTacToe {

public:
    TicTacToe(int board_size = 3);
    void dipslay_board(void);

private:
    vector<vector<int> *> *main_game_board;
    static const int MINMUM_BOARD_SIZE = 3;
    void evaluate_program(int error_code);
    int curr_player;

};


#endif //CPP_GAMES_TIC_TAC_TOE_H
