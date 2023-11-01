#include <iostream>

#include <algorithm>
#include "userinterface.h"
#include "disk.h"
#include "filesystem.h"

using namespace std;
//gcc main.cpp -lstdc++
//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
//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
int main(int argc, char* argv[]) {
    // Check if a file name is provided
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <contiguous|chained|indexed>" << endl;
        return 1;
    }

    UserInterface ui;
    FileSystem fs;
    
    string method = argv[1];
    ui.validateMethod(method);

    while(1){
        int choice = ui.getUserOption();
        fs.handler(choice);
    }
}