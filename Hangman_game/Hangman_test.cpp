//
// Created by deathshot on 4/3/18.
//

#include <iostream>
#include <iomanip>
#include "Hangman.h"

using namespace std;

int main(void) {

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
            cerr << "\n\t\t ----> " << setw(2) << "[" << guess_counter + 1 << "]" << " Guesses made so far [";
            cerr << guesses_made << "] <----\n" << endl;

            if (guess_counter == guess_limit && guesses_made != hangman_game->get_guess()) {
                cout << "\n\t[====== FAILED: You failed to guess word. Guessed word is --> [" << hangman_game->get_guess()
                     << "] =======] \n" << endl;
                break;
            }
            ++guess_counter;
        }

        if (guess_counter <= guess_limit) {
            cout << "\n\t[======= SUCCESS: You've finally made a right guess after [" <<  guess_counter << "] trials! Congrats! ========]" << endl;
        }
        cout << "\n\t[ -------------------------- GAME ENDS -------------------------- ]\n" << endl;
    }
    return EXIT_SUCCESS;
}