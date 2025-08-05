// Definition: Software entities (classes, modules, functions) should be open for extension, 
// but closed for modification.

// What does it actually mean?
// > Open for extension → you can add new functionality
// > Closed for modification → you should not change existing tested code to do it
// Goal: Add new features without breaking existing logic

#include <bits/stdc++.h>
using namespace std;

class PaymentProcessor {
public:
    void process(const std::string& paymentMethod) {
        if (paymentMethod == "credit_card") {
            std::cout << "Processing credit card payment..." << std::endl;
        } else if (paymentMethod == "paypal") {
            std::cout << "Processing PayPal payment..." << std::endl;
        } else if (paymentMethod == "upi") {
            std::cout << "Processing UPI payment..." << std::endl;
        } else {
            throw std::runtime_error("Unsupported payment method");
        }
    }
};


// Above code violates OCP because :

/*
    > Every time a new method (like Stripe, Crypto Pay) is added, you have to:

        -    Modify this class
        -    Risk of breaking existing code
        -    Add more if-else
    > It is neither scalable nor maintainable.

    > To fix it, we have to make the code such that there is no need to change 
      the code of the class PaymentProcessor (closed for modification),
      and still add new payment methods in the future (open for extension). 

 */

// Solution : 

// Strategy Interface
class PaymentStrategy {
public:
    virtual void pay() const = 0;
    virtual ~PaymentStrategy() = default;
};

// Concrete Strategies
class CreditCardPayment : public PaymentStrategy {
public:
    void pay() const override {
        std::cout << "Credit card payment processed" << std::endl;
    }
};

class PayPalPayment : public PaymentStrategy {
public:
    void pay() const override {
        std::cout << "PayPal payment processed" << std::endl;
    }
};

class UPIPayment : public PaymentStrategy {
public:
    void pay() const override {
        std::cout << "UPI payment processed" << std::endl;
    }
};

// Context Class
class PaymentProcessor {
private:
    unique_ptr<PaymentStrategy> strategy;
    // smart pointer , it manages a pointer to PaymentStrategy
    //  object and automatically deletes it when no longer needed
    // strategy : Name of variable 
    // it will point to payment method objec



public:
    PaymentProcessor(unique_ptr<PaymentStrategy> strategy):strategy(move(strategy)) {}

    void process() const {
        strategy->pay();
    }
};

int main() {
    // Choose a payment method at runtime
    std::unique_ptr<PaymentStrategy> strategy = std::make_unique<CreditCardPayment>();
    PaymentProcessor processor(std::move(strategy));
    processor.process(); // Output: Credit card payment processed

    // Switch to PayPal
    PaymentProcessor paypalProcessor(std::make_unique<PayPalPayment>());
    paypalProcessor.process(); // Output: PayPal payment processed
}