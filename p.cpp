#include <iostream>
using namespace std;
//gcc p.cpp -lstdc++

int main(int argc, char* argv[]) {
    // Check if a file name is provided
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <file_name>" << endl;
        return 1;
    }

    string instlist =   "\n1) Display a file\n"
                        "2) Display the file table\n"
                        "3) Display the free space bitmap\n"
                        "4) Display a disk block\n"
                        "5) Copy a file from the simulation to a file on the real system\n"
                        "6) Copy a file from the real system to a file in the simulation\n"
                        "7) Delete a file\n"
                        "8) Exit\n";
    int userChoice;
    while(1){
        cout << instlist << endl;
        std::cout << "Choice: ";
        cin >> userChoice;

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