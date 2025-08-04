#include<bits/stdc++.h>
using namespace std;

class NotificationService{
    public:
    virtual void send(const string& userId, const string & message)=0;
    virtual ~NotificationService() = default;
};

class EmailService : public NotificationService{

    public:
        void send(const string& userId,const string& message){
                cout<<"Email send : "<<"\n";
        }
};

class DummyNotification : public NotificationService{
    public:
        void send(const string& userId, const string& message){
            throw runtime_error("Disabled in testing environment");
        }
};


void notify(NotificationService* service){
    service->send("u123","Your ticket is booked!");
}

int main(){

    try{
        EmailService emailservice;
        DummyNotification dummyservice;
        notify(&emailservice);
        notify(&dummyservice);
    }
    catch(const exception &e){
        cerr << "Exception " << e.what()<<"\n";
    }

    return 0;
}