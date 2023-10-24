//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

int main() {

    string line;
    string command;
    string argument;
    string commandList[6] = {"maxShapes", "create", "move", "rotate", "draw", "delete"};
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        // the next lineStream stringstream will take in the input's argument... i think.
        
        if (command == commandList[0]) { //maxShapes

        // error check number of arguments (only one possible, value)

            if (lineStream.eof()) { //fileStream has reached the end of input after command, 
                                    //indicating no argument
                cout << "Error: too few arguments" << endl;
            } else {
                // take in argument(s)
                lineStream >> max_shapes;

                if (lineStream.fail() ) { //checking for incorrect argument
                    cout << "Error: invalid argument" << endl;
                    lineStream.clear();
                } else if (!lineStream.eof()) { //checking that there are too many args
                    cout << "Error: too many arguments" << endl;
                    lineStream.clear();
                } else { //made it through all error checking. output

                cout << "New database: max shapes is " << max_shapes << endl;

                }
            }

        } else if (command == commandList[1]) { // create

        } else if (command == commandList[2]) { //move

        } else if (command == commandList[3]) { //rotate

        } else if (command == commandList[4]) { //draw

        } else if (command == commandList[5]) { //delete

        } else { 
            cout << "Error: invalid command" << endl;
        }

        

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}

