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
    cout << "\n\t[ ++++++++++++++++++++++ HANGMAN GAME ++++++++++++++++++++++]" << endl;
    cout << "\n\tEnter path to file containing data: ";
    cin >> file_path;

    Hangman *hangman_game = new Hangman(file_path);

    if (hangman_game->game_is_ready()) {
        hangman_game->display_words();
        cout << endl;

        int guess_counter = 0;
        int guess_limit;
        string guesses_made = "";
        cout << "\t[ =================== COMPUTER HAS GUESSED A WORD =============== ] " << endl ;

        cout << "\n\tPlease enter limit for guesses [integer]: ";
        cin >> guess_limit;
        cout << "\n\t[ -------------------------- GAME ON ---------------------------- ]\n" << endl;
        while (guesses_made != hangman_game->get_guess()) {
            string tmp_str = "";
            cout << "\tEnter your guess [a character]: ";
            cin >> tmp_str;
            if (tmp_str.length() != 1) {
                cerr << "\n\t ##### Provide a SINGLE valid character ###### \n" << endl;
                cin.clear();
                continue;
            }

            guesses_made = hangman_game->test_guess(tmp_str);
            cout << "\n\t\t ----> " << setw(2) << "[" << guess_counter + 1 << "]" << " Guesses made so far [";
            cerr << guesses_made << "] <----\n" << endl;

            if (guess_counter == guess_limit && guesses_made != hangman_game->get_guess()) {
                cout << "\n\t[====== FAILED: You failed to guess word. Guessed word is --> [" << hangman_game->get_guess()
                     << "]\n" << endl;
                break;
            }
            ++guess_counter;
        }

        if (guess_counter < guess_limit) {
            cout << "\n\t[======= SUCCESS: You've finally made a right guess after [" <<  guess_counter << "] trials! Congrats! ========]" << endl;
        }
        cout << "\n\t[ -------------------------- GAME ENDS -------------------------- ]\n" << endl;
    }
    return EXIT_SUCCESS;


}