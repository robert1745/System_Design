#include<bits/stdc++.h>
using namespace std;



// SRP principle example
// class Ticketbooking{
//     private:
//         int movieId;
//         int userId;
//         string seatNumber;
    
//     public:

//     Ticketbooking(int movieId, int userId, string seatNumber){
//         this->movieId = movieId;
//         this->userId = userId;
//         this->seatNumber = seatNumber;
//     }

//     bool checkAvailablity(){
//         // to check seat in db
//         return true;
//     }

//     int calculatePrice(){
//         // price logic based on seat type and timing
//         return 100;
//     }

//     bool makePayment() {
//         // Simulate payment gateway
//         return true;
//     }

//     void sendConfirmation(){
//         // send sms or email
//     }

// };

// Problems with above code : 
/***

This code violates SRP principle because it has 4 logical reasons to change :

-> Seat checking logic changes
-> Price policy 
-> Payment gateway changes
-> Notification/Confirmation logic changes

Payment and prices are handled by different teams, so any change in them would require
changes in the class -> So this violates SRP principle.

 ***/

// Solution to above code :

// WE will split into multiple classes 

class SeatChecker{
public:
    bool isSeatAvailable(int movieId, string seatNumber) {
        // check in db if the seat is available
        return true; 
    }
};

class PriceCalculator{
public:
    int getPrice(int movieId, string seatNumber) {
        // logic to calculate price based on seat type and timing...
        return 100; 
    }
};

class PaymentService{
public:
    bool processPayment(int userId, int amount) {
        // Simulate payment gateway
        cout << "Processing payment of " << amount << " for user " << userId << endl;
        return true; 
    }
};

class NotificationService{
public:
    void sendConfirmation(int userId, int movieId) {
        // send sms or email
        cout << "Confirmation sent to user " << userId << " for movie " << movieId << endl;
    }
};


// New Ticketbooking class using SRP principles
class Ticketbooking{
    private:
        SeatChecker &seatchecker;
        PriceCalculator &pricecalculator;
        PaymentService &paymentservice;
        NotificationService &notificationservice;

    public:
        Ticketbooking(SeatChecker &seatchecker, 
            PriceCalculator &pricecalculator, PaymentService &paymentservice,
            NotificationService &notificationservice):
            seatchecker(seatchecker), pricecalculator(pricecalculator),
            paymentservice(paymentservice), notificationservice(notificationservice) {
            }


        void bookTicket(int userId, int movieId, const string& seatNumber) {
        if (seatchecker.isSeatAvailable(movieId, seatNumber)) {
            int price = pricecalculator.getPrice(movieId, seatNumber);
            bool paid = paymentservice.processPayment(userId, price);
            if (paid) {
                notificationservice.sendConfirmation(userId, movieId);
                cout << "Booking successful!" << endl;
            } else {
                cout << "Payment failed!" << endl;
            }
        } else {
            cout << "Seat not available!" << endl;
        }
    }
};


int main(){

    // Ticketbooking ticket(1, 101, "A1");
    // if(ticket.checkAvailablity()){
    //     int price = ticket.calculatePrice();
    //     cout << "Ticket booked successfully. Price: " << price << endl;
    //     ticket.sendConfirmation();
    // } else {
    //     cout << "Seat not available." << endl;
    // }

    SeatChecker seatchecker;
    PriceCalculator pricecalculator;
    PaymentService paymentservice;
    NotificationService notificationservice;

    Ticketbooking ticketbooking(seatchecker, pricecalculator, paymentservice, notificationservice);
    ticketbooking.bookTicket(1, 101, "A1");

    return 0;
}