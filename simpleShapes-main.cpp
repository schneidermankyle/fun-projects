//
//  main.cpp
//  Polymorphism Inheritance
//
//  Created by Kyle Schneiderman on 7/30/14.
//  Copyright (c) 2014 Kyle Schneiderman. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const double PI = 3.14;

// Our shape interface class, as denoted by leading I
class IShape {
protected:
    int _corners;
    double _area;
    
public:
    
    virtual int getCorners() = 0;
    virtual double getArea() = 0;
    
};


// Our rectangle class that is an extension of IShape
class Rectangle : public IShape {
private:
    double _height;
    double _width;
    
public:
    // For game render demonstration
    virtual int getId() { return 0; }
    virtual void update() {
        _width -= 10;
    }
    
    // Expanding our initial functionality of shape class by adding a way to update fields.
    void setHeight(double height){ _height = height; }
    void setWidth(double width){ _width = width; }
    
    // Linking back to our interface class from the virtual pointer table to allow referancing interface object
    virtual double getArea(){ return _height * _width; }
    virtual int getCorners() { return 4; }
};

// Our square class that is an extension of IShape
class Square : public IShape {
private:
    double _width;
    
public:
    // Similar to above, we are simply adding some extra functionaility
    void setWidth(double width){ _width = width; }
    
    // And again setting our Vtable pointers so we can access from interface
    virtual double getArea(){ return _width * _width; }
    virtual int getCorners() { return 4; }
};

// Lastly our circle class that is also an extension of IShape
class Circle : public IShape {
private:
    double _radius;
    
public:
    double getRadius() { return _radius; }
    void setRadius(double rad) { _radius = rad; }
    
    virtual int getCorners() { return 0; }
    virtual double getArea() { return PI * _radius * _radius; }
};


// displaySummary looks for a pointer to type shape and then summarizes the information we set through children classes
void displaySummary(IShape* shape) {
    cout << "Or in summation, this shape has " << shape->getCorners() << " corners and an area of " << shape->getArea() << "\n\n\n";
}

// Quick demonstration of how we can set and call information through interface
int main()
{
    double input;
    int choice;
    bool done = false;
    
    // There are better ways to call and set up your classes, however this will work for this simple demo
    Circle circle;
    Square square;
    Rectangle rectangle;
    
    // As long as user wants to continue, keep looping
    while (!done) {
        cout << "What type of shape would you like to calculate?\n";
        cout << "1: Circle\n";
        cout << "2: Rectangle\n";
        cout << "3: Square\n";
        cout << "0: To exit\n";
        
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Ok great! What is the radius of your cicle? \n";
                cin >> input;
                
                // Set the circle's radius by user input
                circle.setRadius(input);
                cout << "The area of your circle is: " << circle.getArea() << " \n";
                
                // Grab our summary.
                displaySummary(&circle);
                
                break;
                
            case 2:
                
                cout << "Ok great! What is the height of your rectangle? \n";
                cin >> input;
                
                rectangle.setHeight(input);
                
                cout << "How about the width of your Rectangle? \n";
                cin >> input;
                
                rectangle.setWidth(input);
                
                cout << "The area of your rectangle is: " << rectangle.getArea() << " \n";
                
                displaySummary(&rectangle);
                
                break;
                
                
            case 3:
                cout << "Ok great! What is the width of your square? \n";
                cin >> input;
                
                square.setWidth(input);
                
                cout << "Graet! the area of your square is: " << square.getArea() << " \n";
                
                displaySummary(&square);
                
                break;
                
            case 0:
                cout << "Thanks for playing along! \n";
                
                done = true;
                break;
            default:
                cout << "Error that was not a choice \n";
                
                break;
        }
    }
    
    cin.get();
    return 0;
}

