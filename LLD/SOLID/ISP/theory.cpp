#include <bits/stdc++.h>
using namespace std;

// Theory
/*

Definition: Clients should not be forced to depend on interfaces they do not use.

In simple English: Don’t make classes implement methods they don’t need.
Break large interfaces into smaller, focused ones.

*/

// Example to understand behaviour

class RemoteControl
{
public:
    void turnOn() {};
    void turnOff() {};
    void record() {};
};

// Suppose, above interface is implemented by TV and Camera
// TV: supports turnOn/Off
// Camera: supports turnOn/Off,record

// But forcing TV to implement record() voilates ISP.



// Points to remember : 

// Split large interfaces into small, role-based contracts
// Don’t force classes to depend on things they don’t use
// Avoid throw new Error("Not implemented")