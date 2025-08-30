#include <iostream>
#include "helpers.h"
#include "library.h"





void handle_command(int com_id, vector<string> &params, library &currentLibrary){

    switch (com_id) {

        case 0: {   //add NAME AUTHOR ISBN
            currentLibrary.addBook(params[1], params[2], params[3], "No genre");
        } break;


        case 1: {   //remove ISBN
            try {
                currentLibrary.removeBook(params[1]);
            } catch (runtime_error e){
                cout << "Error: " << e.what() << endl;
            }
        } break;


        case 2: {   //search REQUEST
            vector<book> res = currentLibrary.searchBooks(params[1]);
            if (res.empty()){
                cout << "No books with the line found." << endl;
            } else {
                cout << "Found " << res.size() << " books:" << endl;
                for (int i = 0; i < res.size(); i++){
                    cout << res[i].description() << endl;
                }
            }
        } break;


        case 3: {   // register NAME EMAIL ROLE(default=student)
            if (params.size()==3){
                params.push_back("guest");
            }
            try {
                size_t id = currentLibrary.registerUser(params[1], params[2], params[3]);
                cout << "registered successfully! ID = " << id << endl;
            } catch (runtime_error e){
                cout << e.what() << endl;
            }
        } break;


        case 4: {   //return ISBN
            try {
                float fine = currentLibrary.returnBook(params[1]);
                cout << "Book returned";
                if (fine > 0.05){
                    cout << ", due to overdue the fine is " << fine;
                }
                cout << endl;
            } catch (runtime_error e) {
                cout << "Error! " << e.what() << endl;
            }
        } break;


        case 5: {   //borrow ID ISBN
            try {
                currentLibrary.borrowBook(stoi(params[1]), params[2]);
            } catch (runtime_error e){
                cout << "Error: " << e.what() << endl;
            } catch (exception e){
                cout << "Error: " << e.what() << endl;
            }
        } break;


        case 6: {   //getoverdue
            vector<string> res;
            if (params.size() > 1){
                int u_id = -1;
                try {
                    u_id = stoi(params[1]);
                    u_id = currentLibrary.accessUser(u_id)->getId();
                    res = currentLibrary.getOverdueBooks(u_id);
                } catch (exception e){
                    cout << "Error: " << e.what() << endl;
                }
            } else {
                res = currentLibrary.getOverdueBooks();
            }
            if (res.empty()){
                cout << "All books are within time bounds" << endl;
            } else {
                cout << "Found " << res.size() << " overdue books:" << endl;
                for (int i = 0; i < res.size(); i++){
                    cout << currentLibrary.findBook(res[i]).description() << endl;
                }
            }
        } break;


        case 8: {   //history NUMBER
            try {
                int number = -1;
                if (params.size() > 1) {
                    number = stoi(params[1]);
                }
                cout << currentLibrary.showLastActions(number) << endl;
            } catch (exception e){
                cout << "Error showing history" << endl;
            }
        } break;


        default: {
            cout << "UNEXPECTED ERROR 213" << endl;
        }

    }

}


int main() {




    /*


    add NAME AUTHOR ISBN
    remove ISBN
    search REQUEST
    register NAME EMAIL
    return ISBN
    borrow ID ISBN
     getoverdue
    ShowHistory {NUMBER}


     */


    vector<command> allcommands = {{"add", 3, 3, "add (TITLE AUTHOR ISBN) - add a book to the library", 0},
                                   {"remove", 1, 1, "remove (ISBN) - remove a book from the library", 1},
                                   {"search", 1, 1, "search (REQUEST) - search the library for a book with a quote", 2},
                                   {"register", 2, 3, "register (NAME EMAIL {ROLE}) - register a new user, shows the given id", 3},
                                   {"return", 1, 1, "return (ISBN) - return a borrowed book", 4},
                                   {"borrow", 2, 2, "borrow (ID ISBN) - borrows a book for user", 5},
                                   {"getoverdue", 0, 1, "getoverdue ({ID}) - shows overdue books", 6},
                                   {"exit", 0, 0, "exit () - exit the program", 7},
                                   {"history", 0, 1, "history ({NUMBER}) - show last NUMBER or all actions", 8}};




    cout << "Library management started" << endl << endl;
    for (int i = 0; i < allcommands.size(); i++){
        cout << allcommands[i].desc << endl;
    }
    cout << endl << "===============" << endl << endl;


    string rawInput;
    getline(cin, rawInput);
    vector<string> params = parse(rawInput);

    library currentLibrary(false);

    //Matching the command
    while (params.empty() || params[0] != "exit") {
        int com_id = -1;
        for (int i = 0; i < allcommands.size(); i++){
            try {
                auto result = allcommands[i].checkCommand(params);
                if (result.first != -1){
                    com_id = result.first;
                    break;
                }
            } catch (runtime_error e){
                cout << e.what() << endl;
                com_id = -2;
            }
        }

        //Handling wrong commands
        if (com_id < 0){
            if (com_id == -2) {
                cout << "Wrong command parameters." << endl;
            } else if (com_id == -1){
                cout << "Unknown command." << endl;
                for (auto &com : allcommands){
                    cout << com.desc << endl;
                }
                cout << endl;
            }
            cin.clear();
        } else {
            handle_command(com_id, params, currentLibrary);
        }


        cout << endl << "===============" << endl << endl;

        getline(cin, rawInput);
        params = parse(rawInput);
    }




    return 0;
}
