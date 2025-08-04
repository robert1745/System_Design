#include<bits/stdc++.h>
using namespace std;


// Def : If S is a subtype of T, then objects of type T should be replaceable
//  with objects of type S without breaking the program.


// In simple English : You should be able to use a child class anywhere the parent class
//  is expected, and it should work the same, without surprises, bugs, or broken behaviour.



// whats idea behind : 

// > Child classes should respect the behaviour expected from their parent.
// > Inheritance should be behaviorally correct, not just syntactically valid.
// > If a derived class violates the expectations of the base class, it breaks LSP


// class Rectangle {
// protected:
//     int width, height;

// public:
//     Rectangle(int w, int h) : width(w), height(h) {}

//     virtual void setWidth(int w) {
//         width = w;
//     }

//     virtual void setHeight(int h) {
//         height = h;
//     }

//     int getArea() const {
//         return width * height;
//     }
// };

// class Square : public Rectangle {
// public:
//     Square(int size) : Rectangle(size, size) {}

//     void setWidth(int w) override {
//         width = w;
//         height = w;
//     }

//     void setHeight(int h) override {
//         width = h;
//         height = h;
//     }
// };



// void printArea(Rectangle& rect) {
//     rect.setWidth(5);
//     rect.setHeight(10);
//     cout << rect.getArea() << endl; // Expected: 50
// }

// int main() {
//     Rectangle rect(2, 3);
//     printArea(rect);  // OK → 50

//     Square square(2);
//     printArea(square);  // WRONG → 100

//     return 0;
// }


//   So what's the problem?
/*

The problem is:

> The function printArea was written assuming that setting width and height individually
  does not interfere with each other.

> But the Square breaks that assumption: changing width also changes height, and vice versa.

> This breaks the expected behavior, even though Square is a subclass of Rectangle.

*/


// Solution : 

//  We will break down this into  by depending on abstraction (Shape) 
//  and having Rectangle and Square provide their own implementation of getArea().


class Shape {
public:
    virtual int getArea() const = 0;  // Pure virtual function
    virtual ~Shape() = default;       // Virtual destructor for safe polymorphism
};

class Rectangle : public Shape {
private:
    int width, height;

public:
    Rectangle(int w, int h) : width(w), height(h) {}

    int getArea() const override {
        return width * height;
    }
};

class Square : public Shape {
private:
    int side;

public:
    Square(int s) : side(s) {}

    int getArea() const override {
        return side * side;
    }
};

void printArea(const Shape& shape) {
    cout << shape.getArea() << endl;
}

int main() {
    Rectangle rect(5, 10);
    Square square(10);

    printArea(rect);   // 50
    printArea(square); // 100

   return 0;
}