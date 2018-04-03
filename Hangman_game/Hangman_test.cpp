//
// Created by deathshot on 4/3/18.
//

#include <iostream>
#include "Hangman.h"
using namespace std;

int main(void) {
    Hangman *hangman_game = new Hangman();
    vector<string> words = {"first", "second", "man", "oceans", "king",
                      "family", "uncle", "usher", "listen", "learn",
                      "playing", "checking", "creating", "designing",
                      "flying", "nursing"};
    for (unsigned int i = 0; i < words.size(); i++)
        hangman_game->add_word(words.at(i));

    cout << "\n################ WORD DATABASE ################\n" << endl;
    hangman_game->display_words();

}