//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Rectangle here

#include "Triangle.h"
#include "Shape.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

Triangle::Triangle(string n, float x1, float y1, float x2, float y2,
float x3, float y3):Shape(n, (x1+x2+x3)/3, (y1+y2+y3)/3) {

    xc1 = x1;
    xc2 = x2;
    xc3 = x3;
    yc1 = y1;
    yc2 = y2;
    yc3 = y3;

}

Triangle::~Triangle() {
    // maneee
}

void Triangle::draw() const {

    // Set floating point printing to fixed point with 2 decimals
    cout << std::fixed;
    cout << std::setprecision(2);

    cout << "triangle: "<<name<<" "<< x_centre << " " <<y_centre<<" "
    <<xc1<<" "<<yc1<<" "<<xc2<<" "<<yc2<<" "<<xc3<<" "<<yc3<<" "
    <<computeArea()<<endl;

    //triangle: name xcen ycen x1 y1 x2 y2 x3 y3 area

}     // Prints triangle information
    
float Triangle::computeArea() const {

    // area = Ax(By - Cy) + Bx(Cy - Ay) + Cx(Ay - By) divided by 2

    return abs(    (    (xc1*(yc2 - yc3))+(xc2*(yc3-yc1))+(xc3*(yc1-yc2))    )/2    );

}   // Computes the area of the triangle
    
Shape* Triangle::clone() const {

    return (new Triangle(*this));
}  // Clones the object
