#include "users.h"








size_t Generic_user::getId() {return userId_;}

void Generic_user::giveByIsbn(string &isbn){
    if (holding.contains(isbn)){
        holding.erase(isbn);
    } else {
        throw runtime_error("User doesnt have a book with given isbn");
    }
}

void Generic_user::takeBook(Book &n_book){
    holding.insert(n_book.getIsbn());
}

bool Generic_user::hasBook(string &isbn){
    if (holding.contains(isbn)){
        return true;
    }
    return false;
}

bool Generic_user::canBorrow(){
    return holding.size() < getMaxBooks();
}


float Generic_user::getOverdueFine(chrono::steady_clock::duration overdue) {
    return getFinePerDay() * (chrono::duration_cast<chrono::days>(overdue-1s).count()+1);   //rounding up
}

string Generic_user::represent() {
    return name_ + " (id=" + to_string(getId()) + ")";
}















































