/**
 * common.cpp
 * CSE 332S
 * Lab Num: 3
 * Author: 
 * Common function definitions
*/

#include "common.h"
#include <iostream>
#include <string>

using namespace std;

int usage_message (string program_name, string message) {
    cout << "usage: " << program_name << " " << message << endl;
    return incorrect_usage;
}

