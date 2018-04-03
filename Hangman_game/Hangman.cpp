//
// Created by deathshot on 4/2/18.
//

#include <iostream>
#include "Hangman.h"
using namespace std;

#define WORD_FIRST_CHAR         0
#define ASSERT_NOT_NULL(node)   ((node) != nullptr)
#define HARSH_TABLE_SIZE        26

// FOR ERROR HANDLING

#define MEMORY_ALLOC_ERROR      100
#define INVALID_CHAR            101
#define INSERT_FAILURE          false
#define INSERT_SUCCESS          true

#define CANNOT CREATE

const string Hangman::letters[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
                                   "k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
                                   "u", "v", "w", "x", "y", "z"};

int index_equivalent_from_char(char some_char); 

Hangman::Hangman() {
    this->hash_table = new vector<WORD_NODE_ptr_t >(HARSH_TABLE_SIZE);
    ASSERT_NOT_NULL(this->hash_table);
    this->initialize_hash_table();
}

void Hangman::initialize_hash_table() {
    for (int i = 0; i < this->hash_table->size(); i++) {
        this->hash_table->at(i) = (WORD_NODE_ptr_t)malloc(sizeof(WORD_NODE_t));
        if (this->hash_table->at(i) == nullptr) {
            this->handle_error_level(MEMORY_ALLOC_ERROR);
            return;
        }
        // By default all the node pointers in hash table point
        // to themselves (this is my definition of an empty 'hash node' ie.
        // the node that will links series of other nodes at a particular index.
        // (or an empty linked list associated with a node).

        this->hash_table->at(i)->prev_node = this->hash_table->at(i);
        this->hash_table->at(i)->next_node = this->hash_table->at(i);
    }
}

bool Hangman::add_word(string &new_word) {
    if (new_word.size() == 0) {
        cerr << "[WARNING] Empty string cannot be added" << endl;
        return INSERT_FAILURE;
    }
    int hash_index = index_equivalent_from_char(new_word.at(WORD_FIRST_CHAR));
    if (hash_index == INVALID_CHAR) {
        cerr << "[WARNING] Cannot add word '" << new_word << "'. It's invalid" << endl;
        return INSERT_FAILURE;
    }
    return this->insert_hash_word(hash_index, new_word);
}

bool Hangman::insert_hash_word(unsigned int index, string &word) {

    // From our definition of emtpy node, an empty node index point
    // to itself.
    if (this->hash_table->at(index)->next_node == this->hash_table->at(index)) {
        WORD_NODE_ptr_t new_node = (WORD_NODE_ptr_t)malloc(sizeof(WORD_NODE_t));
        ASSERT_NOT_NULL(new_node);
        new_node->word = word;
        new_node->next_node = nullptr;
        new_node->prev_node = this->hash_table->at(index);
        this->hash_table->at(index)->next_node = new_node;
        // we won't handle the 'hash node' 'prev_node' pointer as we won't need it.

        return INSERT_SUCCESS; // we return 'true' because we've inserted it into the structure.
    } else {
        WORD_NODE_ptr_t tmp_ptr = this->hash_table->at(index);
        WORD_NODE_ptr_t new_node = (WORD_NODE_ptr_t)malloc(sizeof(WORD_NODE_t));
        ASSERT_NOT_NULL(new_node);
        do {
            if (tmp_ptr->word == word) {
                // word found in hash table already. We don't insert it again
                return INSERT_FAILURE;

            } else if (tmp_ptr->word > word) {

                tmp_ptr->prev_node->next_node = new_node;
                new_node->prev_node = tmp_ptr->prev_node;
                tmp_ptr->prev_node = new_node;
                new_node->next_node = tmp_ptr;
                new_node->word = word;

                return INSERT_SUCCESS;
            } else if (tmp_ptr->word < word) {
                if (tmp_ptr->next_node == nullptr) {
                    tmp_ptr->next_node = new_node;
                    new_node->next_node = nullptr;
                    new_node->prev_node = tmp_ptr;
                    new_node->word = word;

                    return INSERT_SUCCESS;
                }
                tmp_ptr = tmp_ptr->next_node;
            }
        } while (tmp_ptr != nullptr);

        // If execution reaches this point it means we're at the end of the
        // 'hash node linked list' and we've to insert at that
    }
}


void Hangman::display_words() const {

    for (unsigned int i = 0; i < this->hash_table->size(); i++) {
        cout << "'" << Hangman::letters[i] << "' words --> ";
        WORD_NODE_ptr_t tmp_ptr = this->hash_table->at(i);
        if (tmp_ptr->next_node == nullptr) {
            cout << "[No words yet]" << endl;
            continue;
        }
        while (tmp_ptr->next_node != nullptr) {
            cout << tmp_ptr->word << " | ";
            tmp_ptr = (WORD_NODE_ptr_t) tmp_ptr->next_node;
        }
    }
}

void Hangman::handle_error_level(int error_code) {
    // do some error processing here...
}

int index_equivalent_from_char(char some_char) {
    int shift = -1;
    switch (some_char) {
        case 'a' : return shift + 1; 
        case 'b' : return shift + 2; 
        case 'c' : return shift + 3; 
        case 'd' : return shift + 4; 
        case 'e' : return shift + 5; 
        case 'f' : return shift + 6; 
        case 'g' : return shift + 7; 
        case 'h' : return shift + 8; 
        case 'i' : return shift + 9;  
        case 'j' : return shift + 10;  
        case 'k' : return shift + 11;  
        case 'l' : return shift + 12;  
        case 'm' : return shift + 13;  
        case 'n' : return shift + 14;  
        case 'o' : return shift + 15;
        case 'p' : return shift + 16;
        case 'q' : return shift + 17;
        case 'r' : return shift + 18;
        case 's' : return shift + 19;
        case 't' : return shift + 20;
        case 'u' : return shift + 21;
        case 'v' : return shift + 22;
        case 'w' : return shift + 23;
        case 'x' : return shift + 24;
        case 'y' : return shift + 25;
        case 'z' : return shift + 26;

        default: return INVALID_CHAR;
    }
}
