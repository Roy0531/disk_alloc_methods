#include <iostream>
#include <algorithm>
#include "userinterface.h"
#include "filesystem.h"

using namespace std;
//gcc main.cpp -lstdc++
//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
int main(int argc, char* argv[]) {
    int choice;
    UserInterface ui;

    // working
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <contiguous|chained|indexed>" << endl;
        return 1;
    }
    string method = argv[1];
    // working
    if(ui.validateMethod(method) == -1){
        return 1;
    };

    FileSystem fs(method);
    
    while(true) {
        choice = ui.getUserOption();
        switch(choice){
            case 1: fs.displayFile(); break;
            case 2: fs.displayFileTable(); break;
            case 3: fs.displayBitmap(); break;
            case 4: fs.displayDiskBlock(); break;
            case 5: fs.copyToReal(); break;
            case 6: fs.copyToSimu(); break;
            case 7: fs.deleteFile(); break;
            case 8: cout << "Bye!\n" << endl; return 0 ;
            default: cout << "Please choose one of the valid options listed above" << endl; cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
