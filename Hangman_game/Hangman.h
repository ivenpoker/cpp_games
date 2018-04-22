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
    /**
     * Initializes the Hangman game
     */
    explicit Hangman();

    /**
     * Initializes the Hangman game using a file containing data.
     * The data in file could be english words, sentences or anything
     * that could be accepted as a word.
     * @param data_file_path Path to file containing data
     */
    explicit Hangman(string &data_file_path);

    /**
     * Initializes the Hangman game using a vector of strings i.e.
     * An 'array' of words.
     */
    explicit Hangman(vector<string>);

    /**
     * Adds a word in the Hangman game database.
     * @param new_word New word to add into database
     * @return <code>true</code> if the word was successfully inserted else <code>false</code>
     */
    bool add_word(string &new_word);

    /**
     * Provides a visual display of the database.
     */
    void display_words() const;

    /**
     * Determines if a guess is set for the game
     * @return <code>true</code> if a guess has been set, else <code>false</code>
     */
    bool is_guess_set() const;

    /**
     * Returns the guessed word (done by the 'computer').
     * @return Guessed word done by computer
     */
    string get_guess() const;

    /**
     * Sets a new word (guessed by 'computer')
     */
    void set_guess();

    /**
     * Test whether the guess string (<code>guess_char</code>) passed as parameter
     * is a the guessed word. If its not, the 'set' of guesses made so far is returned
     * as string.
     * @param guess_string String to validate if it's the guessed word.
     * @return Guessed words so far in the game.
     */
    string test_guess(string &guess_string);

    /**
     * Checks if the games is ready.
     * @return <code>true</code> if the game is ready else <code>false</code>
     */
    bool game_is_ready() const;


private:

    // This is word structure (how a word is considered in the program
    typedef struct word_node {
        word_node *prev_node;
        string word;
        word_node *next_node;
    } WORD_NODE_t, *WORD_NODE_ptr_t;

    // This is a structure used in the hash-table implementation
    // that will point to a list of words begining with a particular letter
    typedef struct index_node {
        int index_count;
        WORD_NODE_ptr_t index_node;
    } INDEX_NODE_t, *INDEX_NODE_ptr_t;


    ifstream *client_file;                      // pointer to file containing data.
    vector<INDEX_NODE_ptr_t > *hash_table;      // hash-table to hold all words
    WORD_NODE_ptr_t guessed_word_ptr;           // pointer to guessed word withing data structure.
    string guessed_string_track;                // string to keep track of all correct guesses made so far.

    bool is_game_ready;                         // holds the game status.

    /**
     * Builds the hash table.
     */
    void initialize_hash_table();

    /**
     * When a word has been hashed (a particular index choosen for word),
     * this function will insert that word at the particular index in an
     * orderly manner (i.e in a lexicographical manner).
     * @param index Index to insert word at.
     * @param word Word to be inserted at a particular index
     * @return <code>true</code> if the word was inserted, else <code>fasle</code>
     */
    bool insert_hash_word(unsigned int index, string &word);

    /**
     * This function is intended to be the core of the Hangman game error handling
     * mechanism. It handles errors based on their prescribed codes. Error codes
     * defines the error level.
     * @param error_code Error code to handle. s
     */
    void handle_error_level(int error_code) const;


    /**
     * Letters of the alphabet that are used by Hash-table to know where
     * exactly to place a word.
     */
    static const string letters[];
};


#endif //CPP_GAMES_HANGMAN_H
