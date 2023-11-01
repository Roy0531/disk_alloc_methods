#include <iostream>
using namespace std;

class FileSystem {
private:
    int choice;
public:
    void handler(int choice){
        switch(choice){
            case 1: cout << "You chose 1" << endl; break;
            case 2: cout << "You chose 2" << endl; break;
            case 3: cout << "You chose 3" << endl; break;
            case 4: cout << "You chose 4" << endl; break;
            case 5: cout << "You chose 5" << endl; break;
            case 6: cout << "You chose 6" << endl; break;
            case 7: cout << "You chose 7" << endl; break;
            case 8: cout << "Bye!\n" << endl; exit(0);
            default: cout << "Please choose one of the options listed above" << endl; break;
        }
    }
};