#include<bits/stdc++.h>
using namespace std;

// Does that mean we should only have 1 method per class? : No

// A class should only contain those methods or logic 
// that would change for the same reason in the future.

// Fromm example-1
class Ticketbooking {
    bool checkAvailability();
    int calculatePrice();
    bool makePayment();
    void sendConfirmation();
};

/*

This class violates SRP because:

Seat logic might change → DB schema update

Price logic might change → business policy update

Payment logic might change → gateway switch

Confirmation logic might change → move from SMS to WhatsApp

Each is a separate reason to change, so they should be in separate classes.

*/


// Example-1

class Order{

private:
        vector<string> items;

public:
        void addItem(const string&item){
            items.push_back(item);
        }

        void removeItem(const string& item) {
            items.erase(remove(items.begin(), items.end(), item), items.end());
        }

        int getTotalPrice() const{
            return items.size()*100;
        }
};

// Does this violate SRP?
// No, because all methods are related to one thing : managing contents of an order


// Example-2
struct UserProfile{
    string name;
    string email;
    string profilePicture;
};

class UserProfileManager{
    UserProfile getProfile(int userId){
        // Fetch user from DB

    }

    void updateProfile(int userId,const optional<UserProfile>&data){
        // Save new user profile

    }

    void uploadProfilePicture(int userId, const string& imagePath){
        // Save image to S3

    }

    void deleteAccount(int userId){
        // Delete user from DB and clear sessions

    }

};

// Does this violate SRP?
// Yes , All methods seem “user-related” — so devs assume it’s a single responsibility.
//  But it is not following SRP.

/*** 

> getProfile, updateProfile are similar. They only change when the user's data changes.
> uploadProfilePicture changes when infra changes. Suppose you are storing an image in AWS S3,
  if tomorrow you start storing an image in Cloudflare R2, then uploadProfilePicture changes.
> deleteAccount: It can happen due to many reason like policy violation, inactivity etc. 
  Means this method changes when your business policy changes.

 ***/

// Solution : 

class UserProfileService{
public:
    UserProfile get(int userId){
        // fetch user from db
    }

    void update(int userId,const optional<UserProfile>&data){
        // save new user profile 
    }
};

class UserPictureService{
public:
    void upload(int userId,const string& filePath){
        // save image to S3
    }
};

class UserAccountManager{
public:
    void deleteAccount(int userId){
        // delete user from DB and clear sessions
    }
};



// Example-3

class NotificationService {
public:
    void sendEmail(const string& to, const string& message) {
        // send email
    }

    void sendSMS(const string& to, const string& message) {
        // Send SMS
    }

    void sendPush(const std::string& to, const string& message) {
        // Push Notification

    }
};

// The above code is also violating SRP.

/***

> Suppose you use sendGrid to send email, Twilio to sendSMS and firebase to sendPush,
  so above class changes due to 3 sources. 
If tomorrow you start using AWS SES for emails, then class changes,
if you start using Nexmo to sendSMS then class changes so it has multiple sources
that can change this class. We need to split this into 3 classes
where each class changes due to a single reason.

 
***/


// Solution : 

class EmailSender {
public:
    void send(const std::string& to, const std::string& message) {
        std::cout << "Sending Email to " << to << ": " << message << std::endl;
    }
};

class SmsSender {
public:
    void send(const std::string& to, const std::string& message) {
        std::cout << "Sending SMS to " << to << ": " << message << std::endl;
    }
};

class PushSender {
public:
    void send(const std::string& to, const std::string& message) {
        std::cout << "Sending Push Notification to " << to << ": " << message << std::endl;
    }
};


// Example - 4

class BlogService {
public:
    void createPost(const std::string& title, const std::string& content) {
        std::cout << "Post saved to DB" << std::endl;
    }

    void updatePost(int postId, const std::string& content) {
        std::cout << "Post updated" << std::endl;
    }

    void deletePost(int postId) {
        std::cout << "Post deleted" << std::endl;
    }

    void publish(int postId) {
        std::cout << "Post published" << std::endl;
    }

    void unpublish(int postId) {
        std::cout << "Post unpublished" << std::endl;
    }

    std::string generateShareLink(int postId) {
        return "https://blog.com/share/" + std::to_string(postId);
    }

    void postToTwitter(int postId) {
        std::string link = generateShareLink(postId);
        std::cout << "Tweet posted with link: " << link << std::endl;
    }

    void notifyFollowers(int postId) {
        std::cout << "Followers notified about post " << postId << std::endl;
    }

    void notifyAdmins(int postId) {
        std::cout << "Admins notified about post " << postId << std::endl;
    }
};

// Above code violates SRP 

/*
> create/update/delete post is CRUD and changes when db changes.
> publish, unpublish is related to business logic and policy.
> generateLink, postToTwitter changes when sharing policy or external APIs of social media changes
> notifyFollowers, notifyAdmins changes when communication logic changes.

*/


// Solution : 
class PostRepository {
public:
    void create(const std::string& title, const std::string& content) {
        std::cout << "Post saved to DB" << std::endl;
    }

    void update(int postId, const std::string& content) {
        std::cout << "Post updated" << std::endl;
    }

    void remove(int postId) { // 'delete' is a reserved keyword in C++
        std::cout << "Post deleted" << std::endl;
    }
};

class PublisherService {
public:
    void publish(int postId) {
        std::cout << "Post published" << std::endl;
    }

    void unpublish(int postId) {
        std::cout << "Post unpublished" << std::endl;
    }
};

class SharingService {
public:
    std::string generateShareLink(int postId) {
        return "https://blog.com/share/" + std::to_string(postId);
    }

    void postToTwitter(int postId) {
        std::string link = generateShareLink(postId);
        std::cout << "Tweet posted with link: " << link << std::endl;
    }
};

class NotificationService {
public:
    void notifyFollowers(int postId) {
        std::cout << "Followers notified via email/SMS for post " << postId << std::endl;
    }

    void notifyAdmins(int postId) {
        std::cout << "Admins notified about post " << postId << std::endl;
    }
};