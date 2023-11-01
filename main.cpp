#include <iostream>

#include <algorithm>
#include "userinterface.h"
#include "disk.h"
#include "filesystem.h"

using namespace std;
//gcc main.cpp -lstdc++
//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
int main(int argc, char* argv[]) {
    // Check if a file name is provided
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <contiguous|chained|indexed>" << endl;
        return 1;
    }

    UserInterface ui;
    
    string method = argv[1];
    ui.validateMethod(method);

    while(1){
        int userChoice = ui.getUserOption();
        
        switch(userChoice){
            case 1: cout << "You chose 1" << endl; break;
            case 2: cout << "You chose 2" << endl; break;
            case 3: cout << "You chose 3" << endl; break;
            case 4: cout << "You chose 4" << endl; break;
            case 5: cout << "You chose 5" << endl; break;
            case 6: cout << "You chose 6" << endl; break;
            case 7: cout << "You chose 7" << endl; break;
            case 8: cout << "Bye!\n" << endl; return 0;
            default: cout << "Please choose one of the options listed above" << endl; break;
        }
    }
}