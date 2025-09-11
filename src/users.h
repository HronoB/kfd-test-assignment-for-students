

#include <vector>
#include <unordered_set>
#include "books.h"
#include <stdexcept>




class Generic_user {
public:

    Generic_user(string name, string email, int userId) : name_(name), email_(email), userId_(userId) {}

    virtual ~Generic_user() = default;

    size_t getId();

    void giveByIsbn(string &isbn);

    void takeBook(Book &n_book);

    bool hasBook(string &isbn);

    bool canBorrow();

    virtual int getMaxBooks() = 0;

    const unordered_set<string> &getHolding(){return holding;}

    float getOverdueFine(chrono::steady_clock::duration overdue);

    string represent();

    virtual chrono::steady_clock::duration getMaxTime() = 0;

private:
    unordered_set<string> holding;
    string name_;
    size_t userId_;
    string email_;
    string number_;

    virtual float getFinePerDay() = 0;
};


class User_student : public Generic_user {
public:
    User_student(string name, string email, int userId) : Generic_user(name, email, userId){}

    virtual ~User_student() = default;
    virtual int getMaxBooks() {return 3;}

private:
    virtual chrono::steady_clock::duration getMaxTime() {
        //return 1s;
        return 24h*14;
    }
    virtual float getFinePerDay() {return 0.5;}
};

class User_guest : public Generic_user {
public:
    User_guest(string name, string email, int userId) : Generic_user(name, email, userId){}

    virtual ~User_guest() = default;
    virtual int getMaxBooks() {return 1;}

private:
    virtual chrono::steady_clock::duration getMaxTime() {return 24h*7;}
    virtual float getFinePerDay() {return 0.5;}
};

class User_faculty : public Generic_user {
public:
    User_faculty(string name, string email, int userId) : Generic_user(name, email, userId){}

    virtual ~User_faculty() = default;
    virtual int getMaxBooks() {return 10;}

private:
    virtual chrono::steady_clock::duration getMaxTime() {return 24h*30;}
    virtual float getFinePerDay() {return 0.5;}
};

class User_none : public Generic_user {
public:
    User_none() : Generic_user("", "", 0){}

    virtual ~User_none() = default;
    virtual int getMaxBooks() {throw runtime_error("user null");}

private:
    virtual chrono::steady_clock::duration getMaxTime() {throw runtime_error("user null");}
    virtual float getFinePerDay() {throw runtime_error("user null");}
};

















































