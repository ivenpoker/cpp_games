cmake_minimum_required(VERSION 3.9)
project(cpp_games)

set(CMAKE_CXX_STANDARD 17)
include_directories(cpp_games)
add_executable(cpp_games main_test.cpp main_test.cpp TicTacToe_game/TicTacToe.cpp TicTacToe_game/TicTacToe.h Hangman_game/Hangman.cpp Hangman_game/Hangman.h Hangman_game/Hangman_test.cpp)