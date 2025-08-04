#include <iostream>
using namespace std;

class NotificationService {
public:
    virtual void send(const string& userId, const string& message) {
        cout << "NotificationService::send\n";
    }
    virtual void log() {
        cout << "NotificationService::log\n";
    }
    virtual ~NotificationService() {}
};

class EmailService : public NotificationService {
public:
    void send(const string& userId, const string& message) override {
        cout << "EmailService::send\n";
    }
    void log() override {
        cout << "EmailService::log\n";
    }
};

class DummyService : public NotificationService {
public:
    void send(const string& userId, const string& message) override {
        cout << "DummyService::send\n";
    }
    void log() override {
        cout << "DummyService::log\n";
    }
};

// A helper to read vtable
void printVTable(NotificationService* obj, const string& name) {
    cout << "\n--- VTABLE DUMP for " << name << " ---\n";

    // reinterpret the pointer to a pointer-to-pointer (vptr)
    void** vptr = *(void***)obj;

    // Print first 3 entries (assuming only 3 virtual functions including destructor)
    for (int i = 0; i < 3; ++i) {
        cout << "vtable[" << i << "] = " << (void*)vptr[i] << "\n";
    }
}
int main() {
    NotificationService* base = new NotificationService();
    NotificationService* email = new EmailService();
    NotificationService* dummy = new DummyService();

    base->send("u1", "msg");
    email->send("u2", "msg");
    dummy->send("u3", "msg");

    printVTable(base, "NotificationService");
    printVTable(email, "EmailService");
    printVTable(dummy, "DummyService");

    delete base;
    delete email;
    delete dummy;

    return 0;
}
