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
// Game object interface
class IGameObject {
public:
    virtual int getId() = 0;
    virtual void update() = 0;
};

// Our shape interface class, as denoted by leading I
class IShape {
protected:
    int _corners;
    double _area;
    
public:
    
    virtual int getCorners() = 0;
    virtual double getArea() = 0;
    
};

// We create an engine responsible for updating and rendering objects out
class Engine {
private:
    // Instantiate a blank vector of gameobject pointers
    vector<IGameObject*> _gameObjects;
    
public:
    // We take the pointer of the passed in game object and push it in to the vector
    void add(IGameObject* gameObject) {
        _gameObjects.push_back(gameObject);
    }
    
    // When update is called, we loop through all the game objects and call the shapes update method
    void update() {
        for (auto i = _gameObjects.begin(); i != _gameObjects.end(); i++) {
            (*i)->update();
        }
    }
    
    // When render is called, we loop through all the objects in the vector and process them
    void render() {
        for (auto i = _gameObjects.begin(); i != _gameObjects.end(); i++) {
            // We check to see if current object in vector is a shape so we can render it out
            auto shape = dynamic_cast<IShape*>(*i);
            // If shape cannot be casted and returns NULL, skip it
            if (shape == NULL) {
                continue;
            }
            
            cout << "Rendering shape with area: " << shape->getArea() << "\n";
        }
    }
    

};

// Our rectangle class that is an extension of IShape
class Rectangle : public IShape, public IGameObject {
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
class Square : public IShape, public IGameObject {
private:
    double _width;
    
public:
    // For game render demonstration
    virtual int getId() { return 0; }
    virtual void update() {
        _width -= 5;
    }
    
    // Similar to above, we are simply adding some extra functionaility
    void setWidth(double width){ _width = width; }
    
    // And again setting our Vtable pointers so we can access from interface
    virtual double getArea(){ return _width * _width; }
    virtual int getCorners() { return 4; }
};

// Lastly our circle class that is also an extension of IShape
class Circle : public IShape, public IGameObject {
private:
    double _radius;
    
public:
    // For game render demonstration
    virtual int getId() { return 0; }
    virtual void update() {
        _radius += 2;
    }
    
    double getRadius() { return _radius; }
    void setRadius(double rad) { _radius = rad; }
    
    virtual int getCorners() { return 0; }
    virtual double getArea() { return PI * _radius * _radius; }
};

// Quick class to add a non shape object for demonstrations
class Player : public IGameObject {
public:
    virtual int getId(){ return 0; }
    
    virtual void update() {
        cout << "Doing something\n";
    }
};

// displaySummary looks for a pointer to type shape and then summarizes the information we set through children classes
void displaySummary(IShape* shape) {
    cout << "Or in summation, this shape has " << shape->getCorners() << " corners and an area of " << shape->getArea() << "\n\n\n";
}

// Quick demonstration of how we can set and call information through proper interfaces
int main()
{
    
    Rectangle r1, r2;
    Square s1;
    Circle c1, c2;
    Player p1;
    
    r1.setWidth(100); r1.setHeight(30);
    r2.setWidth(500); r2.setHeight(4000);
    
    s1.setWidth(450);
    
    c1.setRadius(10);
    c2.setRadius(25);
    
    Engine engine;
    engine.add(&r1);
    engine.add(&r2);
    engine.add(&s1);
    engine.add(&c1);
    engine.add(&c2);
    engine.add(&p1);
    
    // Infinate loop to show what's happening in the engine
    while (true) {
        engine.update();
        engine.render();
        
        cout << "Press enter\n";
        cin.get();
    }
    
    return 0;
}

