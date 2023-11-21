//
//
//

#ifndef CSE332LAB_TICTACTOEGAME_H
#define CSE332LAB_TICTACTOEGAME_H

#include <iostream>

/**
 * A piece on the tic tac toe board.
 * Each square will start with 'none', and be updated when someone plays there.
 */
enum class piece {
    X,
    O,
    none
};

/**
 * A game of Tic-Tac-Toe.
 * Stores a 5x5 array of pieces, the current turn, and total number of turns taken.
 */
class TicTacToeGame {
    friend std::ostream& operator<<(std::ostream& os, const TicTacToeGame& game);
    piece board[5][5]; // The game board (only the middle 9 squares will be used)
    piece current_turn; // The piece that will be played next
    unsigned int num_turns; // Total turns taken so far, starts at 0
public:

    /**
     * Initializes current_turn to X, and num_turns to 0.
     * Fills the whole 5x5 board with piece::none
     */
    TicTacToeGame();

    /**
     * Returns true if a player has 3 in a row (vertical, horizontal, or diagonal).
     * Returns otherwise.
     */
    bool done();

    /**
     * Returns true if all 9 squares are full, and neither player has won.
     * Returns false otherwise/
     */
    bool draw();

    /**
     * Prompts the user to input a valid coordinate, and continues
     * doing so until one is received, or the player quits. Sets
     * parameters to input values.
     *
     * @param x the x value, or column, of the new piece
     * @param y the y value, or row, of the new piece
     * @return an int corresponding to the outcome of the function
     */
    int prompt(unsigned int& x, unsigned int& y);

    /**
     * Simulates a turn of Tic Tac Toe. Prints a message saying whose turn it is.
     * Prompts the user to insert valid coordinates until they do so, or they quit.
     * Updates and prints the board with new piece. Prints a list of that players moves.
     * Switches current_turn and increments num_turns.
     *
     * @return an int corresponding to the outcome of the function
     */
    int turn();

    /**
     * Simulates a game of Tic Tac Toe. Prints the empty board.
     * Repeatedly calls the turn method until:
     * The user quits; Prints a message saying the user quit and the number of turns.
     * Someone wins; Prints a message indicating who won.
     * There is a draw; Prints a message saying the game is a draw, and the number of turns.
     *
     * @return
     */
    int play();
};

/**
 * ostream insertion operator overload for TicTacToeGame.
 * Prints the board, with row and column indicators from 0-4.
 * 0,0 is bottom left. 5,5 is top right.
 */
std::ostream& operator<<(std::ostream& os, const TicTacToeGame& game);


#endif //CSE332LAB_TICTACTOEGAME_H
