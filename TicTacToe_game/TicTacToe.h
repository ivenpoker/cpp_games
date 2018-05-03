//
// Created by deathshot on 3/8/18.
//

#ifndef CPP_GAMES_TIC_TAC_TOE_H
#define CPP_GAMES_TIC_TAC_TOE_H

#define INVALID_BOARD_SIZE       (0)
#define INVALID_PLAYER1_MOVE     (1)
#define INVALID_PLAYER2_MOVE     (2)
#define PLAYER1_WINS             (3)
#define PLAYER2_WINS             (4)
#define PLAYER1_TURN             (5)
#define PLAYER2_TURN             (6)
#define CANNOT_MAKE_MOVE         (7)
#define INVALID_BOARD_STATE      (8)
#define INVALID_INDEX_POSITION   (9)
#define INVALID_PLAYER_CODE      (10)
#define MATCH_DRAW               (11)
#define NO_WIN_FOR_PLAYER        (12)
#define END_CURRENT_SESSION      (13)


#include <iostream>
#include <vector>
using namespace std;

// This structure is UNIQUELY used for returning a history of player
// moves back to the user.

typedef struct position_node_list {
    struct position_node_list *next;
    int x_pos;
    int y_pos;
    struct position_node_list *prev;
} POSITION_NODE_LIST_t, *POSITION_NODE_LIST_ptr;

typedef POSITION_NODE_LIST_t ANCHOR_POSITION_LIST_t;
typedef POSITION_NODE_LIST_ptr ANCHOR_POSITION_LIST_ptr;

class TicTacToe {

public:
    static const char PLAYER_ONE = 'X';
    static const char PLAYER_TWO = 'O';


    TicTacToe(int board_size = 3);
    void dipslay_board(void);
    void player1_move(int x_pos, int y_pos);
    void player2_move(int x_pos, int y_pos);
    void reset_game(int board_size = 3);
    int set_player_pos(char player_code, int x_ind, int y_ind );
    void destroy_game(void);
    int get_current_player();
    ANCHOR_POSITION_LIST_ptr get_move_history(char player_char);
    void destroy_moves_history(ANCHOR_POSITION_LIST_ptr);
    ~TicTacToe();



private:
    vector<vector<char> *> *main_game_board;
    static const int MINIMUM_BOARD_SIZE = 3;
    int curr_player;

    // helper functions

    void evaluate_program(int error_code);
    bool validate_indices(char player_code, int ind_x, int ind_y);
    int games_status(char player_code);
    int get_int_equivalent(char player_code, int ind_x, int ind_y);

    void initialize_game(int board_size);
    bool is_valid(char player_code);


};


#endif //CPP_GAMES_TIC_TAC_TOE_H
