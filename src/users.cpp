#include "users.h"








size_t generic_user::getId() {return userId_;}

void generic_user::giveByIsbn(string &isbn){
    if (holding.contains(isbn)){
        holding.erase(isbn);
    } else {
        throw runtime_error("User doesnt have a book with given isbn");
    }
}

void generic_user::takeBook(book &n_book){
    holding.insert(n_book.getIsbn());
}

bool generic_user::hasBook(string &isbn){
    if (holding.contains(isbn)){
        return true;
    }
    return false;
}

bool generic_user::canBorrow(){
    return holding.size() < getMaxBooks();
}


float generic_user::getOverdueFine(chrono::steady_clock::duration overdue) {
    return getFinePerDay() * (chrono::duration_cast<chrono::days>(overdue-1s).count()+1);   //rounding up
}

string generic_user::represent() {
    return name_ + " (id=" + to_string(getId()) + ")";
}















































