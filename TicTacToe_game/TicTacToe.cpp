//
// Created by deathshot on 3/8/18.
//

#include <iostream>
#include <iomanip>
#include "TicTacToe.h"

typedef unsigned long UNSIGNED_LONG;

TicTacToe::TicTacToe(int board_size) {
    if (board_size < TicTacToe::MINMUM_BOARD_SIZE) {
        cerr << "Terminating game now ...." << endl;
        this->evaluate_program(INVALID_BOARD_SIZE);
    }

    // initialize board
    this->main_game_board = new vector<vector<int> *>(board_size, 0);
    for (UNSIGNED_LONG i = 0; i < this->main_game_board->size(); i++) {
        this->main_game_board->at(i) = new vector<int>(board_size, 0);
    }
}

void TicTacToe::evaluate_program(int error_code)  {
    bool exit_program = false;
    if (error_code == INVALID_BOARD_SIZE || error_code == INVALID_BOARD_STATE) {
        cerr << "[ERROR MESSAGE]: ";
    } else {
        cerr << "[WARNING MESSAGE]: ";
    }
    switch (error_code) {
        case INVALID_BOARD_STATE: cerr << "Invalid board state detected"; exit_program = true; break;
        case INVALID_BOARD_SIZE:  cerr << "Invalid board size request detected"; exit_program = true; break;
        case CANNOT_MAKE_MOVE:
            cerr << "Player " << (this->curr_player == PLAYER1_TURN ? "1" : "2") << " cannot make move"; break;
        default:
            cerr << "INTERNAL ERROR DETECTED" << endl; exit_program = true;
            break;
    }
    if (exit_program) {
        exit(EXIT_FAILURE);
    }
}

void TicTacToe::dipslay_board() {
    cout << endl;
    for (UNSIGNED_LONG i = 0; i < this->main_game_board->size(); i++) {
        for (UNSIGNED_LONG j = 0; j < this->main_game_board->size(); j++) {
            cout << setw(4) << this->main_game_board->at(i)->at(j);
        }
        cout << endl;
    }
}




































































































