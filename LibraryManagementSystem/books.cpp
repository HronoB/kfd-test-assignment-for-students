

#include "books.h"



string book::description() {
    string desc = name_ + " (" + genre_ + "), by " + author_ + ". ISBN: " + isbn_;
    return desc;
}

void book::borrow(size_t userId){
    borrowed_at = chrono::steady_clock::now();
    currentUser = userId;
}


bool book::containsQuote(string &s) {
    {
        if (author_.find(s)!=string::npos){
            return true;
        }
        if (name_.find(s)!=string::npos){
            return true;
        }
        if (genre_.find(s)!=string::npos){
            return true;
        }
        return false;
    }
}



bool book::isOverdue(chrono::steady_clock::duration max_dur){
    if (getOverdue(max_dur) > 0s){
        return true;
    }
    return false;
}

chrono::steady_clock::duration book::getOverdue(chrono::steady_clock::duration max_dur){
    chrono::steady_clock::duration diff = chrono::steady_clock::now() - (borrowed_at + max_dur);
    if (diff <= 0s){
        return 0s;
    }
    return diff;
}

void book::setUser(size_t n_user){
    currentUser = n_user;
}

size_t book::getUser(){
    return currentUser;
}

string book::getIsbn(){
    return isbn_;
}

bool book::isFree(){
    return currentUser==0;
}





















