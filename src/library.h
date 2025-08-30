

#include "users.h"
#include <memory>
#include <unordered_map>

class library{


private:

    enum OperationTypes {
        Unknown,
        Borrow,
        Return,
        Register,
        Add,
        Remove
    };

    struct single_operation {

        single_operation(string n_name, string n_desc, int n_type) :
        exec_name(n_name), description(n_desc), time(chrono::steady_clock::now()), type(OperationTypes(n_type)){};

        string exec_name;
        string description;
        chrono::steady_clock::time_point time;
        OperationTypes type;

        string represent();

    };

    bool allowBorrowingIfFined_;
    unordered_map<string, book> storage;

    vector<shared_ptr<generic_user>> allUsers;


public:
    library(bool allowBorrowingIfFined) : allowBorrowingIfFined_(allowBorrowingIfFined), allUsers({make_shared<user_none>()}) { }

    void addBook(string title, string author, string isbn, string genre);

    book &findBook(string isbn);

    void removeBook(string isbn);

    vector<book> searchBooks(string request);

    size_t registerUser(string name, string email, string role);

    float returnBook(string isbn);

    void borrowBook(size_t userId, string isbn);

    vector<string> getOverdueBooks();
    vector<string> getOverdueBooks(size_t user_id);

    float getTotalOverdueFine(size_t user_id);

    size_t registeredUsersCount();

    shared_ptr<generic_user> accessUser(size_t userId);

    vector<single_operation> history;

    string showLastActions(size_t number = -1);

};









































