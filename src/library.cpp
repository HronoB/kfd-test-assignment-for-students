#include "library.h"
#include <stdexcept>
#include "iostream"

void library::addBook(string title, string author, string isbn, string genre) {
    storage[isbn] = book(author, title, isbn, genre);
}

size_t library::registeredUsersCount() {
    return allUsers.size();
}

size_t library::registerUser(string name, string email, string role) {

    shared_ptr<generic_user> nn = nullptr;
    if (role=="student"){
        nn = make_shared<user_student>(name, email, registeredUsersCount());
    } else if (role=="guest"){
        nn = make_shared<user_guest>(name, email, registeredUsersCount());
    } else if (role=="faculty"){
        nn = make_shared<user_faculty>(name, email, registeredUsersCount());
    }

    if (nn == nullptr){
        throw runtime_error("No role found: " + role);
    }

    allUsers.push_back(nn);
    return nn->getId();

}



book &library::findBook(string isbn){
    if (!storage.contains(isbn)){
        throw runtime_error("No book with given isbn exists");
    }
    return storage[isbn];
}

void library::removeBook(string isbn){
    if (!storage.contains(isbn)){
        throw runtime_error("No book with given isbn exists");
    }
    if (!storage[isbn].isFree()) {
        throw runtime_error("Can't remove, the book is currently in use");
    }
    storage.erase(isbn);
}

vector<book> library::searchBooks(string request){

    vector<book> res;
    for (auto &i : storage){
        if (i.second.isFree() && i.second.containsQuote(request)){
            res.push_back(i.second);
        }
    }
    return res;
}

float library::returnBook(string isbn){
    if (!storage.contains(isbn) || storage[isbn].isFree()){
        throw runtime_error("No book with isbn or is already returned");
    }
    auto curr_user = accessUser(storage[isbn].getUser());
    float fine = curr_user->getOverdueFine(storage[isbn].getOverdue(curr_user->getMaxTime()));
    allUsers[storage[isbn].getUser()]->giveByIsbn(isbn);
    storage[isbn].setUser(0);
    return 0.1f*(int)(fine*10+0.999);
}

void library::borrowBook(size_t userId, string isbn){
    shared_ptr<generic_user> curr_user = accessUser(userId);
    if (!storage.contains(isbn)){
        throw runtime_error("No book with such ISBN found");
    }
    if (!storage[isbn].isFree()) {
        throw runtime_error("The book is not available");
    }
    if (!curr_user->canBorrow()){
        throw runtime_error("User can not borrow more than " +
        to_string(curr_user->getMaxBooks()) + " books.");
    }
    if (getOverdueBooks(curr_user->getId()).size() > 0 && !allowBorrowingIfFined_){
        throw runtime_error("User has overdue books");
    }
    curr_user->takeBook(storage[isbn]);
    storage[isbn].borrow(userId);
}


vector<string> library::getOverdueBooks(size_t user_id){
    vector<string> res;
    auto currentUSer = accessUser(user_id);
    for (auto &ib : currentUSer->getHolding()){
        if (storage[ib].isOverdue(currentUSer->getMaxTime())) {
            res.push_back(ib);
        }
    }
    return res;
}

vector<string> library::getOverdueBooks(){
    vector<string> res;
    for (int i = 0; i < registeredUsersCount(); i++){
        for (string &isb : getOverdueBooks(i)){
            res.push_back(isb);
        }
    }
    return res;
}


shared_ptr<generic_user> library::accessUser(size_t userId){
    if (userId >= registeredUsersCount() || userId < 0) {
        throw runtime_error("No user with such ID found");
    }
    return allUsers[userId];
}


float library::getTotalOverdueFine(size_t user_id) {
    float totalFine = 0;
    shared_ptr<generic_user> curr_user = accessUser(user_id);
    for (auto &isb : curr_user->getHolding()){
        totalFine += curr_user->getOverdueFine(storage[isb].getOverdue(curr_user->getMaxTime()));
    }
    return 0.1f*(int)(totalFine*10+0.999);
}






















































