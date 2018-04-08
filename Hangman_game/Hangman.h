//
// Created by deathshot on 4/2/18.
//

#ifndef CPP_GAMES_HANGMAN_H
#define CPP_GAMES_HANGMAN_H

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


class Hangman {

public:
    explicit Hangman();
    explicit Hangman(string &data_file_path);
    explicit Hangman(vector<string>);
    void display_game() const;
    bool add_word(string &new_word);
    void display_words() const;
    bool is_guess_set() const;
    string get_guess() const;
    void set_guess();


private:
    typedef struct word_node {
        word_node *prev_node;
        string word;
        word_node *next_node;
    } WORD_NODE_t, *WORD_NODE_ptr_t;

    typedef struct index_node {
        int index_count;
        WORD_NODE_ptr_t index_node;
    } INDEX_NODE_t, *INDEX_NODE_ptr_t;

    ifstream *client_file;
    vector<INDEX_NODE_ptr_t > *hash_table;
    WORD_NODE_ptr_t guessed_word_ptr;           // pointer to guessed word withing data structure.

    // helper functions
    void initialize_hash_table();
    bool insert_hash_word(unsigned int index, string &word);
    void handle_error_level(int error_code) const;
    void insert_at_end(string word, WORD_NODE_ptr_t node_ptr);

    static const string letters[];
};


#endif //CPP_GAMES_HANGMAN_H
