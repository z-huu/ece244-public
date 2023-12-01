//
//  Rectangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class here

#include "Rectangle.h"
#include "Shape.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

Rectangle::Rectangle(string n, float xcent, float ycent, float w, float h):Shape(n, xcent, ycent) {

    //Shape constructor handles name, xcent, and ycent for us

    width = w;
    height = h;

}


//Destructor
Rectangle::~Rectangle() {
    // Bluh
}

float Rectangle::getHeight() const {

    return height;

}

float Rectangle::getWidth() const {

    return width;

}

void Rectangle::setHeight(float h) {

    height = h;

}    

void Rectangle::setWidth(float w) {

    width = w;

}      

// Utility methods (Inherited from Shape.h)

void Rectangle::draw() const {

    // Set floating point printing to fixed point with 2 decimals
    cout << std::fixed;
    cout << std::setprecision(2);

    cout << "rectangle: "<<name<<" "<< x_centre << " " <<y_centre<<" "
    <<width<<" "<<height<<" "<<computeArea()<<endl;

    //rectangle: name xcen ycen width height area

}     // Prints rectangle information
    
float Rectangle::computeArea() const {

    return abs(width*height);

}   // Computes the area of the rectangle
    
Shape* Rectangle::clone() const {

    return (new Rectangle(*this));
}  // Clones the object