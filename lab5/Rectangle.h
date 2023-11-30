//
//  Rectangle.h
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#ifndef Rectangle_h
#define Rectangle_h

#include <iostream>
#include <string>
#include "Shape.h"
using namespace std;


// This class implements the rectangle Shape objects.
// ECE244 Student: Write the definition of the class here.

class Rectangle : public Shape {

    private:

        float width, height;
        // Inherits name, x_centre, and y_centre from inheriting Shape.h

    public:
    // Constructor. Don't forget to fill out the initializer's list in Rectangle.cpp
    Rectangle (string n, float xcent, float ycent, float w, float h);
    
    // Destructor
    virtual ~Rectangle();
    
    // Accessor
    float getHeight() const;       // Returns the rectangle height
    float getWidth() const;        // Returns the rectangle width

    // Mutator
    void setHeight(float h);       // Sets the height of the circle
    void setWidth(float w);        // Sets the width of the circle
    
    // Utility methods (Inherited from Shape.h)
    virtual void draw() const;     // Prints rectangle information
    
    virtual float computeArea() const;   // Computes the area of the rectangle
    
    virtual Shape* clone() const;  // Clones the object

};

#endif /* Rectangle_h */



