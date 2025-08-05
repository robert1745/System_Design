#include <bits/stdc++.h>
using namespace std;

//  Example-1 : Let's say we wnat to apply offer on movie tickets.

class DiscountEngine
{

    int calculateDiscount(string type, int amount)
    {
        if (type == "student")
        {
            return amount * 0.1;
        }
        else if (type == "seasonal")
        {
            return amount * 0.2;
        }
        return 0;
    }
};

// Problem with this each time new discount appears we need to add if-else ladder
// Violates OCP

// solution :

// Interface (Abstract class )
class DiscountStrategy
{
public:
    virtual int getDiscount(int number) = 0;
    virtual ~DiscountStrategy() = default;
};

class StudentDiscount : public DiscountStrategy
{
public:
    int getDiscount(int amount) override
    {
        return static_cast<int>(amount * 0.1);
    }
};

class SeasonalDiscount : public DiscountStrategy
{
public:
    int getDiscount(int amount) override
    {
        return static_cast<int>(amount * 0.2);
    }
};

class NoDiscount : public DiscountStrategy
{
public:
    int getDiscount(int amount) override
    {
        return 0;
    }
};

// context class
//  what is context class?
/*

“A context class is a class that uses a strategy (or behavior) defined by an interface.
It doesn't implement the logic itself but delegates the responsibility to a strategy object,
which can be changed at runtime. This helps in achieving loose coupling, flexibility,
and adherence to SOLID principles, especially the Open-Closed Principle.”

*/

class DiscountEngine
{
private:
    unique_ptr<DiscountStrategy> discount;

public:
    DiscountEngine(unique_ptr<DiscountStrategy> discount) : discount(move(discount)) {}

    int applyDiscount(int amount)
    {
        return amount - discount->getDiscount(amount);
        ;
    }
};

// This is polymorphism — different objects respond differently to the same method call (getDiscount).

// DiscountEngine is the context that uses a DiscountStrategy.

// This is encapsulation — DiscountEngine wraps all the discount application logic inside itself
//  and exposes only applyDiscount.

// int main(){

//     int amount =100;
//     DiscountEngine studentEngine(make_unique<StudentDiscount>());
//     cout<<"Student discount price : "<<studentEngine.applyDiscount(amount)<<"\n";

//     DiscountEngine seasonalEngine(make_unique<SeasonalDiscount>());
//     cout<<"Season discount price " << seasonalEngine.applyDiscount(amount)<<"\n";

// }

// Example-2 Build a notification system which supports different types of notifications,
//  like email, SMS, sendPush(or pop ) etc

class Notifier
{
public:
    virtual void notify(const string &userId, const string &message) = 0;
    virtual ~Notifier() = default;
};

class EmailNotifier : public Notifier
{
public:
    void notify(const string &userId, const string &message)
    {
        cout << 'Email to ' << userId << ':' << message << "\n";
    }
};

class SMSNotifier : public Notifier
{
public:
    void notify(const string &userId, const string &message)
    {
        cout << 'Sms to ' << userId << ':' << message << "\n";
    }
};

class PushNotifier : public Notifier
{
public:
    void notify(const string &userId, const string &message)
    {
        cout << 'Push notification :' << message << "\n";
    }
};

class NotificationService
{

private:
    vector<unique_ptr<Notifier>> temp;

public:
    // Takes ownership of notifier objects
    NotificationService(vector<unique_ptr<Notifier>> &&notifiers)
        : temp(move(notifiers)) {}

    void sendNotification(const string &userId, const string &message)
    {
        for (const auto &notifier : temp)
        {
            notifier->notify(userId, message);
        }
    }
};

// int main() {
//     vector<unique_ptr<Notifier>> notifiers;
//     notifiers.push_back(make_unique<EmailNotifier>());
//     notifiers.push_back(make_unique<SMSNotifier>());
//     notifiers.push_back(make_unique<PushNotifier>());

//     NotificationService service(move(notifiers));
//     service.sendNotification("naveen@example.com", "You have a new message!");

//     return 0;
// }