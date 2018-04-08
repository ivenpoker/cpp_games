//
// Created by deathshot on 4/3/18.
//

#include <iostream>
#include <iomanip>
#include "Hangman.h"
using namespace std;

int main(void) {
//    Hangman *hangman_game = new Hangman();
//    vector<string> words = {"adam", "asus", "creating", "first", "second", "man", "oceans", "king",
//                      "family", "uncle", "usher", "listen", "learn",
//                      "playing", "checking", "designing",
//                      "flying", "nursing", "zebra", "zoo"};
//    for (unsigned int i = 0; i < words.size(); i++)
//        hangman_game->add_word(words.at(i));
//
//    cout << "\n################ WORD DATABASE ################\n" << endl;
//    hangman_game->display_words();
//
//    string file_path;
//    cout << "Enter path to file: ";
//    cin >> file_path;
//    ifstream client_file(file_path, ios::in);
//
//    if (!client_file) {
//        cerr << "File could not be opened" << endl;
//        exit(EXIT_FAILURE);
//    } else {
//        cout << "FILE IS NOW OPEN" << endl;
//    }
//
//    string node1_value;
//    string node2_value;
//    int edge_value;
//
//    client_file >> node1_value >> node2_value >> edge_value;
//    cout << "File: '" << file_path << "' values" << endl << endl;
//    while (!client_file.eof()) {
//        cout << setw(6) << node1_value << "   " << node1_value << "  " << edge_value << endl;
//        client_file >> node1_value >> node2_value >> edge_value;
//    }

    string file_path;
    cout << "Enter file path: ";
    cin >> file_path;

    Hangman *hangman_game = new Hangman(file_path);

    cout << "\n################ WORD DATABASE ################\n" << endl;
    hangman_game->display_words();
    cout << endl;

    cout << "Guessed word is: " << hangman_game->get_guess() << endl ;


}