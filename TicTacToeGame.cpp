//
// 
//

#include "TicTacToeGame.h"
#include "common.h"
#include <string>
#include <iostream>
#include <regex>
#include <sstream>

using namespace std;

TicTacToeGame::TicTacToeGame() : current_turn(piece::X), num_turns(0) {
    for (auto& col : board) {
        for (auto& p : col) {
            p = piece::none; // initialize all squares to piece::none
        }
    }
}

bool TicTacToeGame::done() {
    // Check each column for 3 in a row
    for (int i = 1; i < 4; ++i) { // JS hardcoded 1, 4
        if (this->board[i][1] == piece::none) { // skip if bottom square is empty
            continue;
        } // JS hardcoded 1,2,3
        if (this->board[i][1] == this->board[i][2] && this->board[i][1] == this->board[i][3]) {
            return true; // bottom square matches middle and top
        }
    }

    // Check each row for 3 in a row
    for (int i = 1; i < 4; ++i) {
        if (this->board[1][i] == piece::none) { // skip if left square is empty
            continue;
        }
        if (this->board[1][i] == this->board[2][i] && this->board[1][i] == this->board[3][i]) {
            return true; // left square matches middle and right
        }
    }

    if (this->board[2][2] == piece::none) { // diagonal impossible if middle is empty
        return false;
    }

    if (this->board[1][1] == this->board[2][2] && this->board[1][1] == this->board[3][3]) {
        return true; // bottom left matches middle and top right
    }

    if (this->board[1][3] == this->board[2][2] && this->board[1][3] == this->board[3][1]) {
        return true; // top left matches middle and bottom right
    }

    return false; // no 3 in a row found
}

bool TicTacToeGame::draw() {
    if (this->done()) {
        return false; // no draw if there's a winner
    }
    // JS hardcoded 4s below
    for (int i = 1; i < 4; ++i) { // middle 3 columns
        for (int j = 1; j < 4; ++j) { // middle 3 rows
            if (this->board[i][j] == piece::none) {
                return false; // no draw if there's an empty square in middle 9
            }
        }
    }
    return true;
}

int TicTacToeGame::prompt(unsigned int& x, unsigned int& y) {
    cout << "Enter coordinates between 1 and 3 in the form 'X,Y' to play a piece." << endl;
    cout << "Enter 'quit' to end the game." << '\n' << endl;

    string str;
    cin >> str;

    if (str == "quit") { // user entered 'quit' to end the game
        return return_value::user_quit;
    }

    // coordinates are poorly formatted or out of bounds
    if ( !regex_match(str, regex("[1-3],[1-3]")) ) {
        cout << '\n' << "Coordinates must be between 1 and 3 in the form 'X,Y'." << endl;
        return this->prompt(x,y); // recursively call prompt() until valid input is found
    }

    str.replace(1,1," "); // replace comma with space for iss extraction operator

    istringstream iss(str);

    // extraction succeeded for both parameters
    if (iss >> x && iss >> y) {
            if (this->board[x][y] != piece::none) { // square is not empty
                cout << '\n' << "That square is taken." << endl;
                return prompt(x,y); // recursively call prompt() until valid input is found
            }
            return return_value::success;
    }
    cout << "Could not extract coordinates" << endl; // Extraction failed on one or both
    return this->prompt(x,y); // recursively call prompt() until valid input is found
}

int TicTacToeGame::turn() {
    if (this->current_turn == piece::X) {
        cout << "It is Player X's turn." << endl;
    }
    else {
        cout << "It is Player O's turn." << endl;
    }

    unsigned int x, y;
    int rv = this->prompt(x,y);
    if (rv != return_value::success) {
        return rv; // return unique error code from prompt
    }

    this->board[x][y] = this->current_turn; // set corresponding square to current_turn's piece value
    cout << '\n' << *this << '\n' << endl; // print the board

    // Print a list of the current player's moves so far
    if (this->current_turn == piece::X) {
        cout << "Player X:";
    }
    else {
        cout << "Player O:";
    }
    for (int i = 1; i < 4; ++i) {
        for (int j = 1; j < 4; ++j) {
            if (this->board[i][j] == this->current_turn) { // the current player has played here
                cout << " " << i << ", " << j << ";" ;
            }
        }
    }
    cout << '\n' << endl;

    // switch current_turn
    if (this->current_turn == piece::X) {
        this->current_turn = piece::O;
    }
    else {
        this->current_turn = piece::X;
    }

    ++num_turns; // increment num_turns only if turn is completed

    return return_value::success;
}

int TicTacToeGame::play() {
    cout << *this << '\n' << endl; // print the board

    // call turn until an end is reached
    while (true) {
        int rv = this->turn();

        // End because the user entered 'quit'
        if (rv == return_value::user_quit) {
            cout << '\n' << "User quit after " << this->num_turns << " turns." << endl;
            return rv;
        }

        // End because someone won
        if (this->done()) {
            if (this->current_turn == piece::X) {
                cout << "Player O won!" << endl;
            }
            else {
                cout << "Player X won!" << endl;
            }
            return return_value::success;
        }

        // End because the board is full and no one won;
        if (this->draw()) {
            cout << this->num_turns << " turns were played. The game is a draw" << endl;
            return return_value::game_draw;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const TicTacToeGame& game) {
    // JS hardcoded 4
    for (int i = 4; i >= 0; --i) { // iterate through rows in reverse order
        os << i; // row marker

        for (auto& col : game.board) { // iterate through columns in proper order
            piece p = col[i];

            // Print piece with leading space
            switch (p) {
                case piece::X:
                    os << " X";
                    break;
                case piece::O:
                    os << " O";
                    break;
                default:
                    os << "  ";
            }
        }
        os << endl;
    }
    os << "  0 1 2 3 4"; // column markers
    return os;
}
