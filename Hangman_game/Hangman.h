//
// Created by deathshot on 4/2/18.
//

#ifndef CPP_GAMES_HANGMAN_H
#define CPP_GAMES_HANGMAN_H

#include <iostream>
#include <vector>
using namespace std;


class Hangman {

public:
    explicit Hangman();
    explicit Hangman(vector<string>);
    void display_game() const;
    bool add_word(string &new_word);
    void display_words() const;


private:
    typedef struct word_node {
        word_node *prev_node;
        string word;
        word_node *next_node;
    } WORD_NODE_t, *WORD_NODE_ptr_t;

    vector<WORD_NODE_ptr_t> *hash_table;

    // helper functions
    void initialize_hash_table();
    bool insert_hash_word(unsigned int index, string &word);
    void handle_error_level(int error_code);

    static const string letters[];
};


#endif //CPP_GAMES_HANGMAN_H
