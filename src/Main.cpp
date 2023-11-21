/**
 * Main.cpp
 * CSE 332S
 * Lab Num:
 * Author:
*/

#include "TicTacToeGame.h"
#include "common.h"
#include <string>
#include <cstring>

using namespace std;

// main requires 1 argument of 'TicTacToe', and simulates a game of Tic-Tac-Toe
int main(int argc, char* argv[]) {
    if (argc != indices::num_args || strcmp(argv[indices::game_name], "TicTacToe") != 0) {
        return usage_message(argv[indices::program], "TicTacToe");
    }
    TicTacToeGame game;
    return game.play();
}