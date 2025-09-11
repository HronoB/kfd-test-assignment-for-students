#include <iostream>
#include "library_console.h"



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



    Library currentLibrary(false);  //Do not allow borrowing if has overdue books

    LibraryConsole console(cin, cout);

    while (console.running()){
        console.doOneIter(currentLibrary);
    }



    return 0;
}
