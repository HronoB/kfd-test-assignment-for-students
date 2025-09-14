#include "library_console.h"




void LibraryConsole::representCommands(){
    for (int i = 0; i < allcommands.size(); i++){
        otp << allcommands[i].desc << endl;
    }
}


LibraryConsole::LibraryConsole(basic_istream<char> &n_inp, basic_ostream<char> &n_otp) : inp(n_inp), otp(n_otp) {

    otp << "Library management started" << endl << endl;

    representCommands();

    otp << endl << "===============" << endl << endl;

}


void LibraryConsole::handle_command(int com_id, vector<string> &params, Library &currentLibrary){

    switch (com_id) {

        case 0: {   //add NAME AUTHOR ISBN
            try {
                currentLibrary.addBook(params[1], params[2], params[3], "No genre");
                cout << "Book added: " << currentLibrary.findBook(params[3]).description() << endl;
            } catch (invalid_argument e){
                cout << "Error: " << e.what() << endl;
            }
        } break;


        case 1: {   //remove ISBN
            try {
                currentLibrary.removeBook(params[1]);
            } catch (runtime_error e){
                otp << "Error: " << e.what() << endl;
            }
        } break;


        case 2: {   //search REQUEST
            vector<Book> res = currentLibrary.searchBooks(params[1]);
            if (res.empty()){
                otp << "No books with the line found." << endl;
            } else {
                otp << "Found " << res.size() << " books:" << endl;
                for (int i = 0; i < res.size(); i++){
                    otp << res[i].description() << endl;
                }
            }
        } break;


        case 3: {   // register NAME EMAIL ROLE(default=student)
            if (params.size()==3){
                params.push_back("guest");
            }
            try {
                size_t id = currentLibrary.registerUser(params[1], params[2], params[3]);
                otp << "registered successfully! ID = " << id << endl;
            } catch (runtime_error e){
                otp << e.what() << endl;
            }
        } break;


        case 4: {   //return ISBN
            try {
                float fine = currentLibrary.returnBook(params[1]);
                otp << "Book returned";
                if (fine > 0.05){
                    otp << ", due to overdue the fine is " << fine;
                }
                otp << endl;
            } catch (runtime_error e) {
                otp << "Error! " << e.what() << endl;
            }
        } break;


        case 5: {   //borrow ID ISBN
            try {
                currentLibrary.borrowBook(stoi(params[1]), params[2]);
            } catch (runtime_error e){
                otp << "Error: " << e.what() << endl;
            } catch (exception e){
                otp << "Error: " << e.what() << endl;
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
                    otp << "Error: " << e.what() << endl;
                }
            } else {
                res = currentLibrary.getOverdueBooks();
            }
            if (res.empty()){
                otp << "All books are within time bounds" << endl;
            } else {
                otp << "Found " << res.size() << " overdue books:" << endl;
                for (int i = 0; i < res.size(); i++){
                    otp << currentLibrary.findBook(res[i]).description() << endl;
                }
            }
        } break;


        case 8: {   //history NUMBER
            try {
                int number = -1;
                if (params.size() > 1) {
                    number = stoi(params[1]);
                }
                string toShow = currentLibrary.showLastActions(number);
                if (toShow.size()>1) {
                    otp << toShow << endl;
                } else {
                    otp << "No records yet";
                }
            } catch (exception e){
                otp << "Error showing history" << endl;
            }
        } break;


        default: {
            otp << "UNEXPECTED ERROR 213" << endl;
        }

    }

}


void LibraryConsole::doOneIter(Library &lib){

    if (finished){
        return;
    }

    string rawInput;
    getline(inp, rawInput);
    vector<string> params = parseIntoVector(rawInput);

    //Matching the command
    if (!params.empty() && params[0] == "exit"){
        finished = true;
        return;
    }


    int com_id = -1;
    if (params.empty()){
        com_id = -1;
    } else {
        for (int i = 0; i < allcommands.size(); i++) {
            try {
                auto result = allcommands[i].checkCommand(params);
                if (result.first != -1) {
                    com_id = result.first;
                    break;
                }
            } catch (runtime_error e) {
                otp << e.what() << endl;
                com_id = -2;
            }
        }
    }

    //Handling wrong commands
    if (com_id < 0){
        if (com_id == -2) {
            otp << "Wrong command parameters." << endl;
        } else if (com_id == -1){
            otp << "Unknown command." << endl;
            representCommands();
            otp << endl;
        }
        inp.clear();
    } else {
        handle_command(com_id, params, lib);
    }


    otp << endl << "===============" << endl << endl;


}












