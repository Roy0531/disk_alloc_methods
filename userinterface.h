#include <iostream>
#include <vector>
using namespace std;

class UserInterface {
private:
    string instlist =   "\n1) Display a file\n"
                        "2) Display the file table\n"
                        "3) Display the free space bitmap\n"
                        "4) Display a disk block\n"
                        "5) Copy a file from the simulation to a file on the real system\n"
                        "6) Copy a file from the real system to a file in the simulation\n"
                        "7) Delete a file\n"
                        "8) Exit\n";
    vector<string> methodList = {"contiguous", "chained", "indexed"};
public:
    int validateMethod(string method){
        if (!(find(methodList.begin(), methodList.end(), method) != methodList.end())) {
            cerr << method << " is not a valid method. \nPlease choose one of the following methods: contiguous|chained|indexed" << endl;
            return -1;
        }
        return 0;
    }

    int getUserOption(){
        int choice;
        cout << instlist << endl;
        cout << "Choice: ";
        cin >> choice;

        return choice;
    }
};