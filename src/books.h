#include <string>
#include "chrono"
#include "iostream"
using namespace std;


class book{
public:

    book(){}

    book(const string &n_author, const string &n_name, const string &n_isbn, const string &genre) : author_(n_author),
    name_(n_name), isbn_(n_isbn), genre_(genre), currentUser(0) {}

    void borrow(size_t userId);

    string description();

    bool containsQuote(string &s);

    bool isOverdue(chrono::steady_clock::duration max_dur);

    chrono::steady_clock::duration getOverdue(chrono::steady_clock::duration max_dur);

    void setUser(size_t n_user);

    size_t getUser();

    string getIsbn();

    bool isFree();

private:
    string author_;
    string name_;
    string isbn_;

    string genre_;

    chrono::time_point<chrono::steady_clock> borrowed_at;
    size_t currentUser;
};












































