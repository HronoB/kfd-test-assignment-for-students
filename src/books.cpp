

#include "books.h"



string Book::description() {
    string desc = name_ + " (" + genre_ + "), by " + author_ + ". ISBN: " + isbn_;
    return desc;
}

void Book::borrow(size_t userId){
    borrowed_at = chrono::steady_clock::now();
    currentUser = userId;
}


bool Book::containsQuote(string &s) {
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



bool Book::isOverdue(chrono::steady_clock::duration max_dur){
    if (getOverdue(max_dur) > 0s){
        return true;
    }
    return false;
}

chrono::steady_clock::duration Book::getOverdue(chrono::steady_clock::duration max_dur){
    chrono::steady_clock::duration diff = chrono::steady_clock::now() - (borrowed_at + max_dur);
    if (diff <= 0s){
        return 0s;
    }
    return diff;
}

void Book::setUser(size_t n_user){
    currentUser = n_user;
}

size_t Book::getUser(){
    return currentUser;
}

string Book::getIsbn(){
    return isbn_;
}

bool Book::isFree(){
    return currentUser==0;
}





















