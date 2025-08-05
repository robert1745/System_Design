/*

Suppose your code flows like this:

API -> Controller Layer -> Service Layer -> Repository Layer

In the Controller Layer, you accept the request from the API.
In the Service Layer, you pass the API arguments and do computation and all business logic.
In Repository Layer, you interact with databases or external service to persist or get data.

Suppose we are building a Ticketing booking system. 
Now, we will write code without following DIP.

*/


#include <iostream>
#include <string>
#include <map>

using namespace std;

//////////////////////////////////////////
// Tightly Coupled Version (No DIP)
//////////////////////////////////////////

// Repository Layer (Concrete)
class TicketRepository {
public:
    string bookTicket(const string& userId, const string& movieId) {
        cout << "[No DIP] Saving booking in DB for user " << userId << " and movie " << movieId << "\n";
        return "booking-id-123";
    }
};

// Service Layer tightly coupled with concrete repository
class BookTicketService {
    TicketRepository repo;  // TIGHTLY COUPLED
public:
    string execute(const string& userId, const string& movieId) {
        return repo.bookTicket(userId, movieId);
    }
};

// Controller Layer tightly coupled with service
class BookTicketController {
    BookTicketService service;  // TIGHTLY COUPLED
public:
    map<string, string> handleRequest(const map<string, string>& reqBody) {
        string userId = reqBody.at("userId");
        string movieId = reqBody.at("movieId");
        string bookingId = service.execute(userId, movieId);

        return {
            {"success", "true"},
            {"bookingId", bookingId}
        };
    }
};

//////////////////////////////////////////
// Main function for No-DIP version
//////////////////////////////////////////
void runWithoutDIP() {
    cout << "\n--- Running WITHOUT DIP ---\n";
    BookTicketController controller;

    map<string, string> request = {
        {"userId", "u1"},
        {"movieId", "m101"}
    };

    auto response = controller.handleRequest(request);
    cout << "{ success: " << response["success"]
         << ", bookingId: '" << response["bookingId"] << "' }\n";
}


//////////////////////////////////////////
// DIP-Compliant Version
//////////////////////////////////////////

// Interface
class ITicketRepository {
public:
    virtual string bookTicket(const string& userId, const string& movieId) = 0;
    virtual ~ITicketRepository() = default;
};

// Concrete Repository implementing interface
class TicketRepositoryDIP : public ITicketRepository {
public:
    string bookTicket(const string& userId, const string& movieId) override {
        cout << "[DIP] Saving booking in DB for user " << userId << " and movie " << movieId << "\n";
        return "booking-id-456";
    }
};

// Service depending on abstraction
class BookTicketServiceDIP {
    ITicketRepository* repo;
public:
    BookTicketServiceDIP(ITicketRepository* repository) : repo(repository) {}

    string execute(const string& userId, const string& movieId) {
        return repo->bookTicket(userId, movieId);
    }
};

// Controller depending on injected service
class BookTicketControllerDIP {
    BookTicketServiceDIP* service;
public:
    BookTicketControllerDIP(BookTicketServiceDIP* srv) : service(srv) {}

    map<string, string> handleRequest(const map<string, string>& reqBody) {
        string userId = reqBody.at("userId");
        string movieId = reqBody.at("movieId");
        string bookingId = service->execute(userId, movieId);

        return {
            {"success", "true"},
            {"bookingId", bookingId}
        };
    }
};

//////////////////////////////////////////
// Main function for DIP version
//////////////////////////////////////////
void runWithDIP() {
    cout << "\n--- Running WITH DIP ---\n";
    TicketRepositoryDIP repo;
    BookTicketServiceDIP service(&repo);
    BookTicketControllerDIP controller(&service);

    map<string, string> request = {
        {"userId", "u2"},
        {"movieId", "m202"}
    };

    auto response = controller.handleRequest(request);
    cout << "{ success: " << response["success"]
         << ", bookingId: '" << response["bookingId"] << "' }\n";
}


