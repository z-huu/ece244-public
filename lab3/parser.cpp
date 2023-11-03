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
bool checkValidShape(string type); //true if shape is valid!
bool checkValidName(string name); //true if name is valid!

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

        if (lineStream.fail()) {
            cout << "Error: invalid command" << endl;
            lineStream.clear();
            lineStream.ignore();
        } else if (command == commandList[0]) { //maxShapes

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
                    lineStream.ignore();
                } else if (!lineStream.eof()) { //checking for more than one argument
                    cout << "Error: too many arguments" << endl;
                    lineStream.clear();
                    lineStream.ignore();
                } else if (max_shapes < 0) {
                    cout << "Error: invalid value" << endl;
                    lineStream.ignore();
                } else { //made it through all error checking. output

                    cout << "New database: max shapes is " << max_shapes << endl;

                    //dynamically allocate Shape* array and set all elements to NULL

                    //delete old shapesArray
                    if (shapesArray != NULL) { //if the array is not null, delete the contents
                        for (int i = 0; i < max_shapes; i++) { //delete each element of the array
                            if (shapesArray[i] != NULL) { //if there is a shape at the index
                                delete shapesArray[i];
                                shapesArray[i] = NULL;
                            } else { //if index is empty
                                continue;
                            }
                        }
                        delete [] shapesArray;
                        shapeCount = 0; //should this be here? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    }

                    shapesArray = new Shape*[max_shapes];

                    for (int i = 0; i < max_shapes; i++) {
                        shapesArray[i] = NULL;
                    }

                }
            }

        } else if (command == commandList[1]) { // create

            // 5 arguments to come: name (string), type (string), x pos, y pos, x size, y size
            string name, type;
            int x_pos, y_pos, x_size, y_size;

            if (lineStream.eof()) { //if no arguments are passed
                cout << "Error: too few arguments" << endl;
            } else {

                lineStream >> name;

                if (lineStream.fail()) { //if first argument is invalid
                    cout<< "Error: invalid argument" << endl;
                    lineStream.clear();
                    lineStream.ignore();
                } else if (lineStream.eof()) { //if only one argument was passed
                    cout<< "Error: too few arguments" << endl;
                    lineStream.clear();
                } else if (!checkValidName(name)) { //if name takes on a reserved keyword
                    cout<<"Error: invalid shape name"<<endl;
                } else {

                    lineStream >> type;

                    if (lineStream.fail()) { //if second argument is invalid
                        cout << "Error: invalid argument" << endl;
                        lineStream.clear();
                        lineStream.ignore();
                    } else if (lineStream.eof()) { //if only two arguments are passed
                        cout << "Error: too few arguments" << endl;
                        lineStream.clear();
                    } else if (!checkValidShape(type)) { //checking valid type
                        cout<<"Error: invalid shape type"<<endl;
                    } else {

                        lineStream >> x_pos;

                        if (lineStream.fail()) { //if third argument is invalid
                            cout << "Error: invalid argument" << endl;
                            lineStream.clear();
                            lineStream.ignore();                    
                        } else if (lineStream.eof()) { //if only three arguments are passed
                            cout <<"Error: too few arguments" << endl;
                            lineStream.clear();
                            lineStream.ignore();
                        } else if (x_pos < 0) { 
                            cout <<"Error: invalid value"<<endl;
                        } else {

                            lineStream >> y_pos;

                            if (lineStream.fail()) { //if fourth argument is invalid
                                cout << "Error: invalid argument" << endl;
                                lineStream.clear();
                                lineStream.ignore();                    
                            } else if (lineStream.eof()) { //if only four arguments are passed
                                cout <<"Error: too few arguments" << endl;
                                lineStream.clear();
                                lineStream.ignore();
                            } else if (y_pos < 0) { 
                                cout <<"Error: invalid value"<<endl;
                            } else {

                                lineStream >> x_size;

                                if (lineStream.fail()) { //if fifth argument is invalid
                                    cout << "Error: invalid argument" << endl;
                                    lineStream.clear();
                                    lineStream.ignore();                    
                                } else if (lineStream.eof()) { //if only five arguments are passed
                                    cout <<"Error: too few arguments" << endl;
                                    lineStream.clear();
                                    lineStream.ignore();
                                } else if (x_size < 0) { 
                                    cout <<"Error: invalid value"<<endl;
                                } else {

                                    lineStream >> y_size;

                                    if (lineStream.fail()) { //if sixth argument is invalid
                                        cout << "Error: invalid argument" << endl;
                                        lineStream.clear();
                                        lineStream.ignore();
                                    } else if (!lineStream.eof()) { //if more than six arguments are passed
                                        cout << "Error: too many arguments" << endl;
                                        lineStream.clear();
                                        lineStream.ignore();
                                    } else if (type == "circle"&&(x_size!=y_size)) { //check that x_size and y_size are identical, if shape is a circle
                                        cout << "Error: invalid value"<<endl;
                                    } else if (y_size < 0) { 
                                        cout <<"Error: invalid value"<<endl;
                                    } else { //we made it past error checking. lets create the shape now

                                        if (shapeCount == max_shapes) {
                                            cout << "Error: shape array is full" << endl;
                                        } else {
                                            shapesArray[shapeCount] = new Shape(name, type, x_pos, x_size, y_pos, y_size);
                                            cout << "Created "<<name << ": "<<type<<" "<<  x_pos << " " 
                                            << y_pos << " " << x_size << " " << y_size << endl;
                                            shapeCount++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                } 
            } 
        } else if (command == commandList[2]) { //move, adjusting Shape object's x and y locations
            //move name loc1 loc2

            //variables for inputs
            string name;
            int locX, locY;
            bool foundShape = false;

            if (lineStream.eof()) { //no arguments were passed
                cout << "Error: too few arguments" << endl;
            } else {
                
                lineStream >> name;

                if (lineStream.fail()) { //if first argument is invalid
                    cout<< "Error: invalid argument" << endl;
                    lineStream.clear();
                    lineStream.ignore();
                } else if (lineStream.eof()) { //if only one argument was passed
                    cout<< "Error: too few arguments" << endl;
                    lineStream.clear();
                } else {
                    
                    lineStream >> locX;

                    if (lineStream.fail()) { //if second argument is invalid
                        cout << "Error: invalid argument" << endl;
                        lineStream.clear();
                        lineStream.ignore();
                    } else if (lineStream.eof()) { //if only two arguments were passed
                        cout << "Error: too few arguments" << endl;
                        lineStream.clear();
                    } else if (locX < 0) { 
                        cout <<"Error: invalid value"<<endl;
                    } else {
                        lineStream >>locY;
                        if (lineStream.fail()) { //if third argument is invalid
                            cout << "Error: invalid argument" << endl;
                            lineStream.clear();
                            lineStream.ignore();
                        } else if (!lineStream.eof()) { //if more than three arguments were passed
                            cout << "Error: too many arguments" << endl;
                            lineStream.clear();
                            lineStream.ignore();
                        } else if (locY < 0) { 
                            cout <<"Error: invalid value"<<endl;
                        } else { //we've made it past error checking. let's change the Shape object
                            
                            //search Shapes array for the given name
                            for (int i = 0; i < shapeCount; i++) {
                                if (shapesArray[i]!=NULL&&name == shapesArray[i]->getName()) { //found the Shape
                                    shapesArray[i]->setXlocation(locX);
                                    shapesArray[i]->setYlocation(locY);
                                    foundShape = true;
                                    cout << "Moved " << name << " to " << locX << " " << locY << endl;
                                    i = shapeCount;
                                }

                            }

                            if (!foundShape) {
                                cout << "Error: shape " << name << " not found." << endl; //might be a formatting error here? ~~~~~~~~~~~`
                                foundShape = false;
                            }

                        }
                    }

                }

            }

        } else if (command == commandList[3]) { //rotate

            string name; int angle;
            //2 arguments: name & angle (between 0 and 360)

            if (lineStream.eof()) { //if no arguments were passed
                cout << "Error: too few arguments" << endl;
                lineStream.clear();
                lineStream.ignore();
            } else {

                lineStream >> name;

                if (lineStream.fail()) { //if first argument is invalid
                    cout << "Error: invalid argument" << endl;
                    lineStream.clear();
                    lineStream.ignore();
                } else if (lineStream.eof()) { //if only one argument was passed
                    cout<< "Error: too few arguments" << endl;
                    lineStream.clear();
                    lineStream.ignore();
                } else {

                    lineStream >> angle;

                    if (lineStream.fail()) { //if the second argument is invalid
                        cout << "Error: invalid argument" << endl;
                        lineStream.clear();
                        lineStream.ignore();
                    } else if (!lineStream.eof()) { //if more than two arguments were passed
                        cout << "Error: too many arguments" << endl;
                        lineStream.clear();
                        lineStream.ignore();
                    } else if (angle < 0 || angle > 360) {
                        cout << "Error: invalid value" << endl;
                        lineStream.clear();
                        lineStream.ignore();
                    } else { //made it past error checking
                        bool found = false; int index = 0;
                        //search for shape name in array
                        for (int i = 0; i < max_shapes && !found; i++) {
                            if (shapesArray[i]!=NULL&&name == shapesArray[i]->getName()) { //found the name
                                found = true; index = i;
                            }
                        }
                        if (found) {
                            shapesArray[index]->setRotate(angle);
                            cout << "Rotated " << name << " by " << angle << " degrees" <<endl;
                        } else {
                            cout << "Error: shape " << name << " not found" << endl;
                        }         
                    }
                }
            }
        } else if (command == commandList[4]) { //draw

            string arg;
            //one argument, string could be either name or all
            //printing shape with given name or printing all shapes
            while (lineStream.peek() == 32) { //ignoring spaces after input
                lineStream.ignore(1);
            }

            if (lineStream.eof()) { //no arguments were passed
                cout <<"Error: too few arguments"<<endl;
                lineStream.clear();
                lineStream.ignore();
            } else {

                lineStream >> arg;

            if (lineStream.fail()) { //if argument is invalid
                cout << "Error: invalid argument" << endl;
                lineStream.clear();
                lineStream.ignore();
            } else if (!lineStream.eof()) { //if more than one argument is passed
                cout << "Error: too many arguments" << endl;
                lineStream.clear();
                lineStream.ignore();
            } else {

                if (arg == "all") { //draw all shapes
                    cout << "Drew all shapes " << endl;
                    for (int i = 0; i < shapeCount; i++) { //looping through shapesArray
                        if (shapesArray[i]!=NULL) {
                            cout << shapesArray[i]->getName() <<": "<<shapesArray[i]->getType()<< " "
                            << shapesArray[i]->getXlocation()<<" "<<shapesArray[i]->getYlocation()<<
                            " "<<shapesArray[i]->getXsize()<<" "<<shapesArray[i]->getYsize()<<endl;
                        }
                    }
                    
                } else { //search for shape name;
                    bool found = false;
                    for (int i = 0; i < max_shapes; i++) {
                        if (shapesArray[i]!=NULL) {
                            if (arg == shapesArray[i]->getName()) { //if shape is found
                                cout << "Drew "<< arg <<": " << shapesArray[i]->getType() << " " << 
                                shapesArray[i]->getXlocation() <<" " << shapesArray[i]->getYlocation() << " "
                                << shapesArray[i]->getXsize() <<" "<< shapesArray[i]->getYsize()<<endl;
                                found = true;
                                break;
                            }
                        }
                    }
                    if (!found) { 
                        cout << "Error: shape "<<arg<<" not found"<<endl;
                    }
                }

            }
        }

        } else if (command == commandList[5]) { //delete

            //but if we delete all, we set shapeCount = 0?
            //don't decrement shapeCount after deletion
        } else { 
            cout << "Error: invalid command" << endl;
            lineStream.ignore();
        }

        

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}

bool checkValidShape(string type) { //check passed shape is valid type
    return (type == shapeTypesList[0] || type == shapeTypesList[1] ||
    type == shapeTypesList[2] || type == shapeTypesList[3]); 
    //returns true if type matches any of the accepted shapes
    //string shapeTypesList[4]={"circle", "ellipse", "rectangle","triangle"};
}

bool checkValidName(string name) { //check passed name is not a reserved keyword
    return (name != keyWordsList[0] && name!=keyWordsList[1]&&name!=keyWordsList[2]&&
    name!=keyWordsList[3]&&name!=keyWordsList[4]&&name!=keyWordsList[5]&&name!=
    keyWordsList[6]&&name!=shapeTypesList[0]&&name!=shapeTypesList[1]&&name!=shapeTypesList[2]
    &&name!=shapeTypesList[3]);
    // string keyWordsList[7]={"all", "maxShapes", "create", 
    //"move", "rotate", "draw", "delete"};
}