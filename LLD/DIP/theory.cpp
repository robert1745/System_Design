/* 

DIP : Dependency Inversion Principle

Definition: High-level modules should not depend on low-level modules. 
            Both should depend on abstractions.
            Abstractions should not depend on details. Details should depend on abstractions.

In simple English: Your business logic (high-level) shouldn’t directly depend on
         concrete classes (low-level). Instead, both should depend on interfaces (abstractions).

*/


// without DIP : 

#include<bits/stdc++.h>
using namespace std;


// class Keyboard {
// public:
//     string getInput() { return "Input from Keyboard"; }
// };

// class Computer {
//     Keyboard keyboard; // direct dependency on low-level class
// public:
//     void input() {
//         cout << keyboard.getInput() << endl;
//     }
// };


// correct version code : 

// Abstraction
class InputDevice{
    public:
        virtual string getInput() =0;
        virtual ~InputDevice() = default;
};



// low-level module

class Keyboard : public InputDevice{
    public:
            string getInput(){
                return "Input from keyboard";
            }

};


class TouchScreen : public InputDevice{
    public:
            string getInput(){
                return "Input from touchscreen!";
            }
};


// High level module

class Computer{
    
    InputDevice *input;
    public:
        Computer(InputDevice* device) : input(device){};
    void fxn(){
          cout<< input->getInput()<<"\n";
    }
};

int main(){
    Keyboard k1;
    TouchScreen t1;
    Computer c1(&k1);
    c1.fxn();
    

    return 0;
}