#include<bits/stdc++.h>
using namespace std;

//  Example -1

class PaymentGateway
{
public:
    virtual void pay() = 0;
    virtual void refund() = 0;
    virtual void schedule() = 0;
    virtual ~PaymentGateway() = default;
};

// StripePayment -> Supports all methods
// CashOnDelivery → supports only pay() but forced to implement refund()
//                  and schedule() which it can’t support

class cashonDelivery : public PaymentGateway
{

public:
    void pay()
    {
        cout << "COD payment!";
    }

    void refund(){
        throw  runtime_error("Refund is not supported for COD");
    }

    void schedule(){
        throw  runtime_error("Scheduling  is not supported! ");
    }
};



// Solution :


// Interface: Payable
class Payable {
public:
    virtual void pay() = 0;
    virtual ~Payable() = default;
};

// Interface: Refundable
class Refundable {
public:
    virtual void refund() = 0;
    virtual ~Refundable() = default;
};

// Interface: Schedulable
class Schedulable {
public:
    virtual void schedule() = 0;
    virtual ~Schedulable() = default;
};

// Class: CashOnDelivery implements Payable
class CashOnDelivery : public Payable {
public:
    void pay() override {
        cout << "COD payment" << endl;
    }
};

// Class: StripePayment implements Payable, Refundable, Schedulable
class StripePayment : public Payable, public Refundable, public Schedulable {
public:
    void pay() override {
        cout << "Stripe payment" << endl;
    }

    void refund() override {
        cout << "Stripe refund processed" << endl;
    }

    void schedule() override {
        cout << "Stripe payment scheduled" << endl;
    }
};




// Example-2 


class FileHandler{
    public:
        virtual void open() =0;
        virtual string read()=0;
        virtual void write(string &data)=0;
        virtual void close()=0;
        virtual ~FileHandler() = default;
};

//  LogFileReader: only needs open, read, close
//  LogFileWriter: only needs open, write, close



// LogFileReader: only needs open, read, close
class LogFileReader : public FileHandler {
public:
    void open() override {
        cout << "Opening log file for reading" << endl;
    }

    string read() override {
        return "Reading from log file";
    }

    void write(string &data) override {
        throw runtime_error("Write not supported in LogFileReader");
    }

    void close() override {
        cout << "Closing log file (reader)" << endl;
    }
};

// LogFileWriter: only needs open, write, close
class LogFileWriter : public FileHandler {
public:
    void open() override {
        cout << "Opening log file for writing" << endl;
    }

    string read() override {
        throw runtime_error("Read not supported in LogFileWriter");
    }

    void write(string &data) override {
        cout << "Writing to log file: " << data << endl;
    }

    void close() override {
        cout << "Closing log file (writer)" << endl;
    }
};



// Solution : 

// Interface: FileOpener
class FileOpener {
public:
    virtual void open() = 0;
    virtual void close() = 0;
    virtual ~FileOpener() = default;
};

// Interface: FileReader
class FileReader : public FileOpener {
public:
    virtual string read() = 0;
};

// Interface: FileWriter
class FileWriter : public FileOpener {
public:
    virtual void write(const string& data) = 0;
};

// Class: LogFileReader implements FileReader
class LogFileReader : public FileReader {
public:
    void open() override {
        cout << "Opening file for reading" << endl;
    }

    string read() override {
        return "Reading from log file";
    }

    void close() override {
        cout << "Closing file after reading" << endl;
    }
};

class LogFileWriter : public FileWriter {
public:
    void open() override {
        cout << "Opening file for writing" << endl;
    }

    void write(const string& data) override {
        cout << "Writing to log file: " << data << endl;
    }

    void close() override {
        cout << "Closing file after writing" << endl;
    }
};