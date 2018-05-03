//
// Created by deathshot on 3/8/18.
//

#include <iostream>
#include <iomanip>
#include <cassert>
#include "TicTacToe.h"

typedef unsigned long UNSIGNED_LONG;

typedef struct position {
    int x_pos;
    int y_pos;
} POSITION_t, *POSITION_ptr_t;

POSITION_ptr_t player1_pos;
POSITION_ptr_t player2_pos;


// ################## Data Structure to keep track of ALL player valid moves ####################

// A valid move structure

typedef struct move_node {
    struct move_node *next_ptr;
    POSITION_t position;
    struct move_node *prev_ptr;
} MOVE_NODE_t, *MOVE_NODE_ptr_t;

// Main structure that will hold (point to) all player moves.
typedef struct player_moves {
    MOVE_NODE_ptr_t moves_ptr;
} PLAYER_MOVES_t, *PLAYER_MOVES_ptr_t;

PLAYER_MOVES_ptr_t player1_moves;  // pointer to all player1 valid moves
PLAYER_MOVES_ptr_t player2_moves;  // pointer to all player2 valid moves

void initialize_player_moves(int player_code);
void add_player_move(PLAYER_MOVES_ptr_t player_x_moves, POSITION_t next_move);
ANCHOR_POSITION_LIST_ptr stringify_player_moves(PLAYER_MOVES_ptr_t player_x_moves);


TicTacToe::TicTacToe(int board_size) {
    if (board_size < TicTacToe::MINIMUM_BOARD_SIZE) {
        cerr << "\n\t\tTerminating game now ..." << endl;
        this->evaluate_program(INVALID_BOARD_SIZE);
    }

    // initialize board
    this->initialize_game(board_size);
    this->curr_player = TicTacToe::PLAYER_ONE;

    // Initialize player moves tracker
    initialize_player_moves(TicTacToe::PLAYER_ONE);  // tracker for player1
    initialize_player_moves(TicTacToe::PLAYER_TWO);  // tracker for player2

}

void TicTacToe::initialize_game(int board_size) {
    this->main_game_board = new vector<vector<char> *>(board_size, 0);
    for (UNSIGNED_LONG i = 0; i < this->main_game_board->size(); i++) {
        this->main_game_board->at(i) = new vector<char>(board_size);
        for (UNSIGNED_LONG j = 0; j < this->main_game_board->size(); j++)
            this->main_game_board->at(i)->at(j) = ' ';
    }
    player1_pos = (POSITION_ptr_t)malloc(sizeof(POSITION_t));
    player2_pos = (POSITION_ptr_t)malloc(sizeof(POSITION_t));

    assert(player1_pos != nullptr);
    assert(player2_pos != nullptr);

    player1_pos->x_pos = -1;
    player1_pos->y_pos = -1;

    player2_pos->x_pos = -1;
    player2_pos->y_pos = -1;
}

void TicTacToe::evaluate_program(int game_code)  {
    bool exit_program = false;
    cerr << endl;
    if (game_code == INVALID_BOARD_SIZE || game_code == INVALID_BOARD_STATE) {
        cerr << "\t\t[ERROR MESSAGE]: ";
    } else {
        cerr << "\t\t[WARNING MESSAGE]: ";
    }
    switch (game_code) {
        case INVALID_BOARD_STATE:
            cerr << "Invalid board state detected" << endl;
            exit_program = true; break;

        case INVALID_BOARD_SIZE:
            cerr << "Invalid board size request detected" << endl;
            exit_program = true; break;

        case CANNOT_MAKE_MOVE:
            cerr << "Player " << (this->curr_player == PLAYER1_TURN ? "1" : "2") << " cannot make move" << endl;
            break;
        case INVALID_INDEX_POSITION:
            cerr << "Cannot operate on the chosen indices" << endl;
            break;

        case INVALID_PLAYER_CODE:
            cerr << "Invalid player code." << endl;
            break;
        case INVALID_PLAYER1_MOVE:
            cerr << "Invalid move. Player1 (X) cannot move there." << endl;
            break;
        case INVALID_PLAYER2_MOVE:
            cerr << "Invalid move. Player2 (0) cannot move there." << endl;
            break;

        case END_CURRENT_SESSION:
            exit(EXIT_SUCCESS);

        default:
            cerr << "INTERNAL ERROR DETECTED" << endl; exit_program = true;
            break;
    }
    if (exit_program) {
        exit(EXIT_SUCCESS);
    }
}

int TicTacToe::get_current_player() {
    return this->curr_player;
}

void TicTacToe::dipslay_board() {
    cout << endl;
    for (UNSIGNED_LONG i = 0; i < this->main_game_board->size(); i++) {
        cout << "\t\t\t";
        for (UNSIGNED_LONG j = 0; j < this->main_game_board->size(); j++) {
            cout << setw(4) << this->main_game_board->at(i)->at(j) << "|";
        }
        cout << endl;
        cout << "\t\t\t";
        for (UNSIGNED_LONG k = 0; k < this->main_game_board->size(); k++) {
            if (i == this->main_game_board->size()-1) break;
            cout << setw(5) << "___" << setw(1);
        }
        cout << endl;
    }
    cout << endl;

    // if the player X or O is currently invalid, tell him/her to
    // provide valid indices to continue.

    cout << "\t\t-------------------------------------" << endl;
    if (!is_valid(TicTacToe::PLAYER_ONE)) {
        cout << "\t\tPlayer1 (X) last move -> at [" << player1_pos->x_pos << ", "
             << player1_pos->y_pos << "]" << endl;
    } else {
        cout << "\t\tPlayer1 (X) last move -> no move yet" << endl;
    }
    if (!is_valid(TicTacToe::PLAYER_TWO)) {
        cout << "\t\tPlayer2 (O) last move -> at [" << player2_pos->x_pos << ", "
             << player2_pos->y_pos << "]" << endl;
    } else {
        cout << "\t\tPlayer2 (O) last move -> no move yet" << endl;
    }
    cout << "\t\t-------------------------------------" << endl;
}


bool TicTacToe::is_valid(char player_code) {
    if (player_code == TicTacToe::PLAYER_ONE) {
        return ((player1_pos->x_pos < 0 || player1_pos->x_pos >= this->main_game_board->size()) ||
                 player1_pos->y_pos < 0 || player1_pos->y_pos >= this->main_game_board->size());
    } else if (player_code == TicTacToe::PLAYER_TWO) {
        return ((player2_pos->x_pos < 0 || player2_pos->x_pos >= this->main_game_board->size()) ||
                 player2_pos->y_pos < 0 || player2_pos->y_pos >= this->main_game_board->size());
    }
}

bool TicTacToe::validate_indices(char player_code, int ind_x, int ind_y) {
    if (player_code != TicTacToe::PLAYER_ONE && player_code != TicTacToe::PLAYER_TWO)
        this->evaluate_program(INVALID_PLAYER_CODE);

    UNSIGNED_LONG board_size = this->main_game_board->size();
    if ((ind_x < 0 || ind_x >= board_size) || (ind_y < 0 || ind_y >= board_size)) {
        evaluate_program(INVALID_INDEX_POSITION);
        return false;
    }
    // a player cannot play where someone is already there, even if it's still
    // the same player. if a player made an invalid move we provide an error
    // message addressing the appropriate player.

    if (TicTacToe::PLAYER_ONE == this->main_game_board->at(ind_x)->at(ind_y) ||
        TicTacToe::PLAYER_TWO == this->main_game_board->at(ind_x)->at(ind_y)) {
        if (player_code == TicTacToe::PLAYER_ONE) {
            this->evaluate_program(INVALID_PLAYER1_MOVE);
            return false;
        } else {
            this->evaluate_program(INVALID_PLAYER2_MOVE);
            return false;
        }
    }
    return true;
}


int TicTacToe::set_player_pos(char player_code, int x_ind, int y_ind) {
    if (this->validate_indices(player_code, x_ind, y_ind)) {
        if (player_code == TicTacToe::PLAYER_ONE) {
            player1_pos->x_pos = x_ind;
            player1_pos->y_pos = y_ind;

            // keep track of this position
            add_player_move(player1_moves, *player1_pos);

            this->main_game_board->at(x_ind)->at(y_ind) = TicTacToe::PLAYER_ONE;
            this->curr_player = TicTacToe::PLAYER_TWO;

            // checking if player1 won with last move
            return games_status(TicTacToe::PLAYER_ONE);

        } else if (player_code == TicTacToe::PLAYER_TWO){
            player2_pos->x_pos = x_ind;
            player2_pos->y_pos = y_ind;

            // keep track of this position
            add_player_move(player2_moves, *player2_pos);

            this->main_game_board->at(x_ind)->at(y_ind) = TicTacToe::PLAYER_TWO;
            this->curr_player = TicTacToe::PLAYER_ONE;

            // checking if player2 won with last move
            return games_status(TicTacToe::PLAYER_TWO);
        }
    }
    return NO_WIN_FOR_PLAYER;
}


int TicTacToe::games_status(char player_code) {
    // checking game status for player 1
    int player_code_sum = 0;

    // sum all rows while checking if the player with 'player_code' won

    for (UNSIGNED_LONG i = 0; i < this->main_game_board->size(); i++) {
        for (UNSIGNED_LONG j = 0; j < this->main_game_board->size(); j++) {
            if (this->main_game_board->at(i)->at(j) == player_code) ++player_code_sum;
        }
        if (player_code_sum == this->main_game_board->size())
            return (player_code == TicTacToe::PLAYER_ONE ? PLAYER1_WINS : PLAYER2_WINS);
        player_code_sum = 0;
    }
    player_code_sum = 0;

    // sum all columns while checking if the player with 'player_code' won.

    for (UNSIGNED_LONG i = 0; i < this->main_game_board->size(); i++) {
        for (UNSIGNED_LONG j = 0; j < this->main_game_board->size(); j++)
            if (this->main_game_board->at(j)->at(i) == player_code) ++player_code_sum;
        if (player_code_sum == this->main_game_board->size())
            return (player_code == TicTacToe::PLAYER_ONE ? PLAYER1_WINS : PLAYER2_WINS);
        player_code_sum = 0;
    }

    player_code_sum = 0;
    // ##########################  checking diagonals ##############################/

    // left to right diagonal check

    for (UNSIGNED_LONG k = 0, j = 0; k < this->main_game_board->size(); k++, j++) {
        if (this->main_game_board->at(k)->at(j) == player_code)
            ++player_code_sum;
    }
    if (player_code_sum == this->main_game_board->size())
        return (player_code == TicTacToe::PLAYER_ONE ? PLAYER1_WINS : PLAYER2_WINS);

    player_code_sum = 0;  // At this point we haven't no player has win at left diagonal.

    // top right to bottom left diagonal.

    for (int k = static_cast<int>(this->main_game_board->size()-1), j = 0; k >= 0; k--, j++) {
        if (this->main_game_board->at(k)->at(j) == player_code)
            ++player_code_sum;
    }
    if (player_code_sum == this->main_game_board->size())
        return (player_code == TicTacToe::PLAYER_ONE ? PLAYER1_WINS : PLAYER2_WINS);

    return NO_WIN_FOR_PLAYER;
}

int TicTacToe::get_int_equivalent(char player_code, int ind_x, int ind_y) {
    this->validate_indices(player_code, ind_x, ind_y);
    if (this->main_game_board->at(ind_x)->at(ind_y) == player_code) {
        if (player_code == TicTacToe::PLAYER_ONE)
            return 1;
        else
            return -1;
    }
}

void TicTacToe::reset_game(int board_size) {
    this->initialize_game(board_size);
}

void TicTacToe::destroy_game() {
    for (UNSIGNED_LONG i = 0; i < this->main_game_board->size(); i++)
        delete (this->main_game_board->at(i));
    delete (this->main_game_board);

    // Free pointers for the last move for first and second player
    free(player1_pos);
    free(player2_pos);
}

TicTacToe::~TicTacToe() {
    this->destroy_game();
}

ANCHOR_POSITION_LIST_ptr TicTacToe::get_move_history(char player_char) {
    return (TicTacToe::PLAYER_ONE == player_char ? stringify_player_moves(player1_moves) :
                                                   stringify_player_moves(player2_moves));
}

void TicTacToe::destroy_moves_history(ANCHOR_POSITION_LIST_ptr list_ptr) {
    if (list_ptr == nullptr || list_ptr->next == nullptr) return;
    POSITION_NODE_LIST_ptr curr_del = list_ptr->next;
    POSITION_NODE_LIST_ptr next_del = list_ptr->next->next;

    while (curr_del != nullptr) {
        free(curr_del);
        curr_del = next_del;
        next_del = curr_del->next;
    }
}

void initialize_player_moves(int player_code) {

    if (TicTacToe::PLAYER_ONE == player_code) {
        player1_moves = (PLAYER_MOVES_ptr_t)malloc(sizeof(PLAYER_MOVES_t));
        assert(player1_moves != nullptr);
        player1_moves->moves_ptr = (MOVE_NODE_ptr_t)malloc(sizeof(MOVE_NODE_t));
        assert(player1_moves->moves_ptr != nullptr);
    } else {
        player2_moves = (PLAYER_MOVES_ptr_t)malloc(sizeof(PLAYER_MOVES_t));
        assert(player2_moves != nullptr);
        player2_moves->moves_ptr = (MOVE_NODE_ptr_t)malloc(sizeof(MOVE_NODE_t));
        assert(player2_moves->moves_ptr != nullptr);
    }

//    if (player_x_moves != nullptr) {
//        // this player moves has already been initialized
//        return;
//    }
//    player_x_moves = (PLAYER_MOVES_ptr_t)malloc(sizeof(PLAYER_MOVES_t));
//    if (player_x_moves == nullptr) {
//        cerr << "\n\t\t[GAME WARNING] Cannot track moves for player " << player_code << endl;
//        return;
//    }
//    player_x_moves->moves_ptr = (MOVE_NODE_ptr_t)malloc(sizeof(MOVE_NODE_t));
//    if (player_x_moves->moves_ptr == nullptr) {
//        cerr << "\n\t\t[GAME WARNING] Cannot track moves for player " << player_code << endl;
//    }
}

void add_player_move(PLAYER_MOVES_ptr_t player_x_moves, POSITION_t next_move) {
    if (player_x_moves == nullptr) return;

    MOVE_NODE_ptr_t new_node = (MOVE_NODE_ptr_t)malloc(sizeof(MOVE_NODE_t));

    if (new_node == nullptr) {
        cerr << "\n\t\t[GAME WARNING] Error while recording last move" << endl;

        // At this level, we can completely stop the game (if it's absolutely) important
        // that the game KNOWS all moves made by a player. To do that we can just assert
        // that the 'new_node' is not null (before this if statement):
        //
        //          assert(new_node != nullptr)
        //
        // or we could just also use, 'exit(EXIT_FAILURE)' after printing the error
        // message and terminating the program.

        return;
    }

    new_node->position = next_move;

    // if this is the first move for player

    if (player_x_moves->moves_ptr->next_ptr == nullptr) {
        player_x_moves->moves_ptr->next_ptr = new_node;

        // We are using a doubly linked list to keep track of all player moves.
        // Our chosen implementation is to let the anchor's (main node pointer
        // to the list itself) previous pointer (pointer that is suppose to point
        // tot he previous node) point to the last node i.e we're using a 'circular'
        // doubly linked list to keep track of moves. The idea behind this to
        // provide the possibility in the future to traverse the list from the 'back'.

        player_x_moves->moves_ptr->prev_ptr = new_node;
        new_node->next_ptr = nullptr;
        new_node->prev_ptr = player_x_moves->moves_ptr;

    } else {
        // If there are already moves made to this player's 'move history'

        new_node->next_ptr = player_x_moves->moves_ptr->next_ptr;
        player_x_moves->moves_ptr->next_ptr->prev_ptr = new_node;
        new_node->prev_ptr = player_x_moves->moves_ptr;
        player_x_moves->moves_ptr->next_ptr = new_node;
    }
}

ANCHOR_POSITION_LIST_ptr stringify_player_moves(PLAYER_MOVES_ptr_t player_x_moves) {

    if (player_x_moves == nullptr) return nullptr; // player tracker not initialized
    if (player_x_moves->moves_ptr == nullptr) return nullptr; // player moves not initialized
    if (player_x_moves->moves_ptr->next_ptr == nullptr) return nullptr; // player did not make any moves

    ANCHOR_POSITION_LIST_ptr player_moves_list = (ANCHOR_POSITION_LIST_ptr)malloc(sizeof(ANCHOR_POSITION_LIST_t));
    if (player_moves_list == nullptr) {
        cerr << "\t\t[SYSTEM ERROR] Memory allocation issues" << endl;
        return nullptr;
    }
    MOVE_NODE_ptr_t tmp_move_ptr = (MOVE_NODE_ptr_t ) player_x_moves->moves_ptr->next_ptr;
    while (tmp_move_ptr != nullptr) {
        POSITION_NODE_LIST_ptr node = (POSITION_NODE_LIST_ptr)malloc(sizeof(POSITION_NODE_LIST_t));
        if (node == nullptr) {
            cerr << "\n\t[SYSTEM ERROR] Memory allocation issues" << endl;
            return nullptr;
        }
        node->x_pos = tmp_move_ptr->position.x_pos;
        node->y_pos = tmp_move_ptr->position.y_pos;

        node->next = player_moves_list->next;
        node->prev = player_moves_list;

        if (player_moves_list->next != nullptr)
            player_moves_list->next->prev = node;

        player_moves_list->next = node;
        tmp_move_ptr = tmp_move_ptr->next_ptr;
    }
    return player_moves_list;
}






























































































