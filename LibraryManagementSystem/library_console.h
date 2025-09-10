



#include <vector>
#include <iostream>
#include "library.h"
#include "helpers.h"






class LibraryConsole{
public:



    LibraryConsole(basic_istream<char> &n_inp, basic_ostream<char> &n_otp);



    bool running(){return !finished;}

    void doOneIter(Library &lib);

    void handle_command(int com_id, vector<string> &params, Library &currentLibrary);


private:

    basic_istream<char> &inp;
    basic_ostream<char> &otp;

    bool finished = false;

    void representCommands();

    vector<command> allcommands = {{"add", 3, 3, "add (TITLE AUTHOR ISBN) - adds a book to the library", 0},
                                   {"remove", 1, 1, "remove (ISBN) - removes a book from the library", 1},
                                   {"search", 1, 1, "search (REQUEST) - searches the library for a book with a quote", 2},
                                   {"register", 2, 3, "register (NAME EMAIL {ROLE}) - registers a new user, shows the given id", 3},
                                   {"return", 1, 1, "return (ISBN) - returns a borrowed book", 4},
                                   {"borrow", 2, 2, "borrow (ID ISBN) - borrows a book for user", 5},
                                   {"getoverdue", 0, 1, "getoverdue ({ID}) - shows overdue books", 6},
                                   {"exit", 0, INT_MAX, "exit () - exits the program", 7},
                                   {"history", 0, 1, "history ({NUMBER}) - shows last NUMBER or all actions", 8}};

};



























