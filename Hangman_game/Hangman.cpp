//
// Created by deathshot on 4/2/18.
//

#include <iostream>
#include <iomanip>
#include "Hangman.h"
using namespace std;

#define WORD_FIRST_CHAR         0
#define ASSERT_NOT_NULL(node)   ((node) != nullptr)
#define HARSH_TABLE_SIZE        26
#define INSERT_FAILURE          false
#define INSERT_SUCCESS          true
#define BOOLEAN_TRUE            true
#define BOOLEAN_FALSE           false

// FOR ERROR HANDLING

#define INTERNAL_PROGRAM_FAILURE 99
#define MEMORY_ALLOC_ERROR       100
#define INVALID_CHAR             101
#define NULL_POINTER_REQUEST     102
#define GUESS_NOT_SET            103
#define FILE_NOT_FOUND           404
#define GUESS_NOT_SET_STRING     "[--- guess not set; call 'set_guess()' function --]"
#define INVALID_TEST_STRING      "[--- Provide a valid test string --]";



const string Hangman::letters[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
                                   "k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
                                   "u", "v", "w", "x", "y", "z"};

/**
 * Returns the integer equivalent of a letter of the alphabet
 * (i.e from 0 - 25 (due to indexing in C++))
 */
int index_equivalent_from_char(char some_char);

/**
 * Validates a string as a POSSIBLE word.
 * @param some_string String to validate as word
 * @return <code>true</code> if string is COULD be a valid word, else <code>false</code>
 */
bool is_word(string & some_string);

Hangman::Hangman() {
    this->initialize_hash_table();
}

Hangman::Hangman(string &data_file_path) {

    this->is_game_ready = false;
    this->client_file = new ifstream(data_file_path, ios::in);
    if (!(*this->client_file)) {
        this->handle_error_level(FILE_NOT_FOUND);
    } else {
        this->initialize_hash_table();
        string tmp_str;
        (*this->client_file) >> tmp_str;

        while (!this->client_file->eof()) {
            this->add_word(tmp_str);
            (*this->client_file) >> tmp_str;
        }
        this->is_game_ready = true;
        this->set_guess();
    }
}

void Hangman::initialize_hash_table() {

    this->hash_table = new vector<INDEX_NODE_ptr_t >(HARSH_TABLE_SIZE);
    ASSERT_NOT_NULL(this->hash_table);

    for (unsigned int i = 0; i < this->hash_table->size(); i++) {
        this->hash_table->at(i) = (INDEX_NODE_ptr_t)malloc(sizeof(INDEX_NODE_t));
        if (this->hash_table->at(i) == nullptr) {
            this->handle_error_level(MEMORY_ALLOC_ERROR);
            return;
        }
        // By default all the node pointers in hash table point
        // to themselves (this is my definition of an empty 'hash node' ie.
        // the node that will links series of other nodes at a particular index.
        // (or an empty linked list associated with a node).

        this->hash_table->at(i)->index_node = (WORD_NODE_ptr_t)malloc(sizeof(WORD_NODE_t));
        ASSERT_NOT_NULL(this->hash_table->at(i)->index_node);

        this->hash_table->at(i)->index_node->next_node = nullptr;
        this->hash_table->at(i)->index_node->prev_node = nullptr;
        this->hash_table->at(i)->index_count = 0;
    }
}

bool Hangman::add_word(string &new_word) {
    if (new_word.empty()) {
        cerr << "[WARNING] Empty string cannot be added" << endl;
        return INSERT_FAILURE;
    }

    if (!is_word(new_word)) {
        cerr << "[WARNING] Cannot add '" << new_word << "' as word. It is not a WORD." << endl;
        return INSERT_FAILURE;
    }
    int hash_index = index_equivalent_from_char(new_word.at(WORD_FIRST_CHAR));
    return this->insert_hash_word(static_cast<unsigned int>(hash_index), new_word);
}

bool Hangman::game_is_ready() const {
    return this->is_game_ready;
}

string Hangman::test_guess(string &guess_char)  {
    if (!this->is_guess_set()) {
        return GUESS_NOT_SET_STRING;
    } else if (guess_char.empty()) {
        return guess_char;                      // just return it back to caller
    } else if (guess_char.length() != 1) {
        return INVALID_TEST_STRING;
    }

    string tmp_str;
    string main_guessed_word = this->guessed_word_ptr->word;  // copy of guessed word is made
    for (int i = 0; i < main_guessed_word.length(); i++) {
        if (main_guessed_word.at(i) == guess_char.at(0)) {
            tmp_str += i;
            this->guessed_string_track.at(i) =  guess_char.at(0);
        } else {
            tmp_str += " ";
        }
    }
    return this->guessed_string_track;

}
bool Hangman::insert_hash_word(unsigned int index, string &word) {

    WORD_NODE_ptr_t tmp_ptr = this->hash_table->at(index)->index_node->next_node;
    WORD_NODE_ptr_t new_node = (WORD_NODE_ptr_t)malloc(sizeof(WORD_NODE_t));
    new_node->word = word;
    ASSERT_NOT_NULL(new_node);

    do {
        if (tmp_ptr == nullptr) {
            this->hash_table->at(index)->index_node->next_node = new_node;
            new_node->next_node = nullptr;
            new_node->prev_node = this->hash_table->at(index)->index_node;
            ++this->hash_table->at(index)->index_count;

            return INSERT_SUCCESS;
        }
        if (tmp_ptr->word == word) {
            // word found in hash table already. We don't insert it again
            // we just ignore it, and flag the insertion procedure as a
            // failure.
            return INSERT_FAILURE;

        }

        // If the word to insert is less than the word pointed to by 'tmp_ptr'
        // we insert it before 'tmp_ptr'

        else if (tmp_ptr->word > word) {
            tmp_ptr->prev_node->next_node = new_node;
            new_node->prev_node = tmp_ptr->prev_node;
            tmp_ptr->prev_node = new_node;
            new_node->next_node = tmp_ptr;
            ++this->hash_table->at(index)->index_count;

            return INSERT_SUCCESS;
        }

        // If the word to insert is greater than the word pointed to by 'tmp_ptr'
        // we insert it after 'tmp_ptr', but we also specially handle the case
        // where, 'tmp_ptr' might be the LAST node in the doubly linked list data
        // structure.

        else if (tmp_ptr->word < word) {
            if (tmp_ptr->next_node == nullptr) {
                tmp_ptr->next_node = new_node;
                new_node->next_node = nullptr;
                new_node->prev_node = tmp_ptr;
                ++this->hash_table->at(index)->index_count;

                return INSERT_SUCCESS;
            }
            tmp_ptr = tmp_ptr->next_node;
        }
    } while (tmp_ptr != nullptr);

    // If execution reaches this point, it means we've got an internal problem/
    // At this level, it's wise we flag the user of the problem and terminate the
    // program.

    this->handle_error_level(INTERNAL_PROGRAM_FAILURE);


}

void Hangman::display_words() const {

    cout << "\n\t#################### Hangman Game Word database #################\n" << endl ;
    for (unsigned int i = 0; i < this->hash_table->size(); i++) {
        cout << "\t\t";
        cout << "'" << Hangman::letters[i] << "' words [" << setw(2)
             << this->hash_table->at(i)->index_count << "] --> ";
        WORD_NODE_ptr_t tmp_ptr = this->hash_table->at(i)->index_node->next_node;
        if (tmp_ptr == nullptr) {
            cout << "---" << endl;
            continue;
        }
        cout << "| ";
        while (tmp_ptr != nullptr) {
            cout << tmp_ptr->word << " | ";
            tmp_ptr = tmp_ptr->next_node;
        }
        cout << endl;
    }
    cout << "\n\t#################################################################" << endl ;
}

string Hangman::get_guess() const {
    if (this->is_guess_set()) {
        return this->guessed_word_ptr->word;
    }
    return GUESS_NOT_SET_STRING;
}

void Hangman::set_guess()  {
    srand((unsigned) time(nullptr));  // setting random generator
    auto rand_index = static_cast<unsigned int>(rand() % HARSH_TABLE_SIZE); // getting a random index based on the hashtable size

    while (this->hash_table->at(rand_index)->index_node->next_node == nullptr) {
        int new_index = rand() % HARSH_TABLE_SIZE;

        // making sure the previous random number is different from newly generated one.
        // if they were same, get a new random number again;

        while (new_index == rand_index)
            new_index = rand() % HARSH_TABLE_SIZE;
        rand_index = new_index;
    }

    // At this point we've got a random index with words within it.
    // We need to get now a random word found within that index using
    // the number of words at that 'rand_index'.

    int counter = 0;
    int word_index = rand() % this->hash_table->at(rand_index)->index_count;
    WORD_NODE_ptr_t tmp_ptr = this->hash_table->at(rand_index)->index_node->next_node;

    // while we're not yet at the 'word index' we keep traversing the
    // doubly linked list data structure.

    while (counter != word_index) {
        tmp_ptr = tmp_ptr->next_node;
        ++counter;
    }

    // we've reached the 'word index' we just keep a reference to
    // our guessed word, by setting a pointer to this word.

    this->guessed_word_ptr = tmp_ptr;

    // we now need to initialize the guess string tracker, so that any time a
    // guess is made the program can keep track of the last guess made
    // and provide feedback based on the last guesses

    for (int i = 0; i < this->guessed_word_ptr->word.length(); i++)
        this->guessed_string_track += "_";
}

bool Hangman::is_guess_set() const {
    return this->guessed_word_ptr != nullptr;
}

void Hangman::handle_error_level(int error_code) const {
    switch (error_code) {
        case MEMORY_ALLOC_ERROR:
            cerr << "\n\t[INTERNAL ERROR]: Memory allocation error\n" << endl;
            break;
        case INVALID_CHAR:
            cerr << "\n\t[INPUT ERROR]: Invalid word provided. Check input\n" << endl;
            break;
        case FILE_NOT_FOUND:
            cerr << "\n\t[FILE_NOT_FOUND: 404]: File requested not found\n" << endl;
            break;
        case NULL_POINTER_REQUEST:
            cerr << "\n\t[NULL POINTER]: Null pointer request detected\n" << endl;
            break;
        case INTERNAL_PROGRAM_FAILURE:
            cerr << "\n\t[INTERNAL ERROR]: Internal program error occured\n" << endl;
            break;
        default:
            cerr << "\n\t[INTERNAL ERROR]: Unidentified system error\n" << endl;
    }
}

int index_equivalent_from_char(char some_char) {
    if(some_char >= 'a' &&  some_char <= 'z') {
        return some_char - 'a';
    } else if(some_char >= 'A' && some_char <= 'Z') {
        return some_char - 'A';
    } else
       return INVALID_CHAR;
}

bool is_word(string & some_string) {
    if (some_string.length() == 0) return BOOLEAN_FALSE;
    if (some_string.length() == 1) {
        if (index_equivalent_from_char(some_string.at(0)) == INVALID_CHAR)
            return BOOLEAN_FALSE;
        return BOOLEAN_TRUE;
    }
    size_t size = some_string.length();
    for (size_t i = 0; i < size; i++)
        if (index_equivalent_from_char(some_string.at(i)) == INVALID_CHAR)
            return BOOLEAN_FALSE;
    return BOOLEAN_TRUE;
}
