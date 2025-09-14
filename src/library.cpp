#include "library.h"
#include <stdexcept>

void Library::addBook(string title, string author, string isbn, string genre) {
    if (isbn.size() == 0 || author.size() < 2 || title.size() < 2){
        throw invalid_argument("Too short string");
    }
    if (storage.contains(isbn)){
        throw invalid_argument("Book already added");
    }
    storage[isbn] = Book(author, title, isbn, genre);
    history.emplace_back("Librarian", storage[isbn].description(), Add);
}

size_t Library::registeredUsersCount() {
    return all_users.size();
}

size_t Library::registerUser(string name, string email, string role) {

    shared_ptr<Generic_user> nn = nullptr;
    if (role=="student"){
        nn = make_shared<User_student>(name, email, registeredUsersCount());
    } else if (role=="guest"){
        nn = make_shared<User_guest>(name, email, registeredUsersCount());
    } else if (role=="faculty"){
        nn = make_shared<User_faculty>(name, email, registeredUsersCount());
    }

    if (nn == nullptr){
        throw runtime_error("No role found: " + role);
    }

    all_users.push_back(nn);

    history.emplace_back("Librarian", nn->represent(), Register);
    return nn->getId();

}



Book &Library::findBook(string isbn){
    if (!storage.contains(isbn)){
        throw runtime_error("No book with given isbn exists");
    }
    return storage[isbn];
}

void Library::removeBook(string isbn){
    if (!storage.contains(isbn)){
        throw runtime_error("No book with given isbn exists");
    }
    if (!storage[isbn].isFree()) {
        throw runtime_error("Can't remove, the book is currently in use");
    }

    history.emplace_back("Librarian", storage[isbn].description(), Remove);
    storage.erase(isbn);
}

vector<Book> Library::searchBooks(string request){

    vector<Book> res;
    for (auto &i : storage){
        if (i.second.isFree() && i.second.containsQuote(request)){
            res.push_back(i.second);
        }
    }
    return res;
}

float Library::returnBook(string isbn){
    if (!storage.contains(isbn) || storage[isbn].isFree()){
        throw runtime_error("No book with isbn or is already returned");
    }
    auto curr_user = accessUser(storage[isbn].getUser());
    float fine = curr_user->getOverdueFine(storage[isbn].getOverdue(curr_user->getMaxTime()));
    all_users[storage[isbn].getUser()]->giveByIsbn(isbn);
    history.emplace_back(all_users[storage[isbn].getUser()]->represent(), storage[isbn].description(), Return);
    storage[isbn].setUser(0);
    return round(fine*10)*0.1f;
}

void Library::borrowBook(size_t userId, string isbn){
    shared_ptr<Generic_user> curr_user = accessUser(userId);
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

    history.emplace_back(curr_user->represent(), storage[isbn].description(), Borrow);
}


vector<string> Library::getOverdueBooks(size_t user_id){
    vector<string> res;
    auto currentUSer = accessUser(user_id);
    for (auto &ib : currentUSer->getHolding()){
        if (storage[ib].isOverdue(currentUSer->getMaxTime())) {
            res.push_back(ib);
        }
    }
    return res;
}

vector<string> Library::getOverdueBooks(){
    vector<string> res;
    for (int i = 0; i < registeredUsersCount(); i++){
        for (string &isb : getOverdueBooks(i)){
            res.push_back(isb);
        }
    }
    return res;
}


shared_ptr<Generic_user> Library::accessUser(size_t userId){
    if (userId >= registeredUsersCount() || userId < 0) {
        throw runtime_error("No user with such ID found");
    }
    return all_users[userId];
}


float Library::getTotalOverdueFine(size_t user_id) {
    float total_fine = 0;
    shared_ptr<Generic_user> curr_user = accessUser(user_id);
    for (auto &isb : curr_user->getHolding()){
        total_fine += curr_user->getOverdueFine(storage[isb].getOverdue(curr_user->getMaxTime()));
    }
    return round(total_fine*10)*0.1f;
}




string Library::single_operation::represent(){
    string res = "";
    const time_t time_formatted = chrono::system_clock::to_time_t(chrono::system_clock::now()+(time-chrono::steady_clock::now()));
    res += "At ";
    res += ctime(&time_formatted);
    string operation_desc;
    switch (type) {
        case Add: operation_desc = "added";
            break;
        case Remove: operation_desc = "removed";
            break;
        case Borrow: operation_desc = "borrowed";
            break;
        case Return: operation_desc = "returned";
            break;
        case Register: operation_desc = "registered";
            break;
        case Unknown: operation_desc = "UNKNOWN OPERATION";
            break;
    }
    res += " User " + exec_name + " " + operation_desc + " " + description;
    return res;
}




string Library::showLastActions(size_t number) {
    if (number == -1 || number > history.size()){
        number = history.size();
    }
    string res = "";
    for (int i = history.size()-number; i < history.size(); i++){
        res += history[i].represent() + "\n";
    }
    return res;
}












































