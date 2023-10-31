/**
 * common.h
 * CSE 332S
 * Lab Num: 3
 * Author:
 * Common enum and function declarations
*/

#ifndef CSE332LAB_COMMON_H
#define CSE332LAB_COMMON_H

#include <string>

using namespace std;

// return values for program, passed up through functions
enum return_value {
    success,
    user_quit,
    game_draw,
    incorrect_usage,
};

// indices of argv
enum indices {
    program,
    game_name,
    num_args // The correct number of args, and the correct value of argc
};

/**
 * Prints a helpful usage message indicating proper usage of the program.
 *
 * @param program_name the name of the program
 * @param message a message describing correct usage of the program
 * @return an int corresponding to the error code for incorrect usage
 */
int usage_message (string program_name, string message);


#endif //CSE332LAB_COMMON_H
