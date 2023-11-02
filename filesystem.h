#include <iostream>
using namespace std;

class FileSystem {
private:
    int blockSize = 512;
    Disk d;
public:
    void displayFile(){
        string fn;
        cout << "File name: " << endl;
        cin >> fn;

        return;
    }
    void displayFileTable(){
        cout << "displayFileTable" << endl;
        return;
    }
    void displayBitmap(){
        for (int i = 0; i < blockSize; i++) {
            if ((i != 0) && (i % 32 == 0)) cout << endl; 
            cout << d.read(1, i);
        }
        return;
    }
    void displayDiskBlock(){
        cout << "displayDiskBlock" << endl;
        return;
    }
    void copyToReal(){
        string src, dest;
        cout << "Copy from: " << endl;
        cin >> src;
        cout << "Copy to: " << endl;
        cin >> dest;
        
        return;
    }
    void copyToSimu(){
        string src, dest;
        cout << "Copy from: " << endl;
        cin >> src;
        cout << "Copy to: " << endl;
        cin >> dest;

        return;
    }
    void deleteFile(){
        string fn;
        cout << "File name: " << endl;
        cin >> fn;

        return;
    }

    // void displayFileTable(){
    //     for (int i = 0; i < sizeof(disk[1]); i++) {

    //         if (i % 3 == 0){
    //             cout << "File " << "Name";
    //         } else if (i % 3 == 1){
    //             cout << "Start Block";
    //         } else if (i % 3 == 2){
    //             cout << "Length";
    //         }
    //         cout << disk[1][i] << " ";
    //         if (i % 3 == 0){
    //             cout << endl;
    //         }
    //     }
    // }

};