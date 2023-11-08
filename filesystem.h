#include <iostream>
#include <fstream>
#include <string>
#include <fstream>
#include <cmath>
#include "disk.h"
using namespace std;

const int blockNumber = 256;
const int blockSize = 512;
const int MaxNameLength = 8;

class FileSystem {
    private:
        Disk d;
        string method;
        int fileData1[3] = {};
        int fileData2[2] = {};

        int searchFile(string fileName, string& method){
            string data = d.read(0);

            int fileIdx = data.find(fileName);

            if (fileIdx == -1) {
                cout << "File doesn't exist." << endl; 
                return -1;
            }
            if (method == "contiguous" || method == "chained"){
                int startBlock = fileIdx + 8;
                int length = startBlock + 3;
                int startBlockInt = 0;
                int lengthInt = 0;
                int digit;

                fileData1[0] = fileIdx;

                for (int i = startBlock; i < startBlock+3; i++){
                    if (i == startBlock && data[i] != ' '){
                        digit = data[i] - '0';
                        startBlockInt += 100 * digit;
                    } else if (i == startBlock+1 && data[i] != ' '){
                        digit = data[i] - '0';
                        startBlockInt += 10 * digit;
                    } else if (i == startBlock+2){
                        digit = data[i] - '0';
                        startBlockInt +=  digit;
                    }
                }
                fileData1[1] = startBlockInt;
                
                for (int i = length; i < length+2; i++){
                    if (i == length && data[i] != ' '){
                        digit = data[i] - '0';
                        lengthInt += 10 * digit;
                    } else if (i == length+1){
                        digit = data[i] - '0';
                        lengthInt += digit;
                    }
                }
                fileData1[2] = lengthInt;

            } else {
                int idxBlock = fileIdx + 8;
                int indBlockInt = 0;
                int digit;

                fileData2[0] = fileIdx;

                for (int i = idxBlock; i < idxBlock+3; i++){
                    if (i == idxBlock && data[i] != ' '){
                        digit = data[i] - '0';
                        indBlockInt += 100 * digit;
                    } else if (i == idxBlock+1 && data[i] != ' '){
                        digit = data[i] - '0';
                        indBlockInt += 10 * digit;
                    } else if (i == idxBlock+2){
                        digit = data[i] - '0';
                        indBlockInt +=  digit;
                    }
                }
                fileData2[1] = indBlockInt;
            }
            return 0;
        }
        string getFileName(string prompt){
            string fn;
            int len;
            do{
                cout << prompt;
                cin >> fn;
                len = fn.length();
                if (len > 8) cout << "The fine name can only be up to 8 characters long" << endl;
            } while(len > 8);
            return fn;
        }
    public:
        FileSystem(string m) {
            method = m;
        }
        void displayFile(){
            string fn;
            string data;
            fn = getFileName("File name: ");
            int result = searchFile(fn, method);
            if(result == -1){
                return;
            }
            int arrlen = sizeof(fileData1) / sizeof(fileData1[0]);
            if (arrlen == 0) {
                return;
            }
            if (method == "contiguous" || method == "chained"){
                int start  = fileData1[1];
                int length = fileData1[2];
                if (method == "contiguous"){
                    for (int i = start; i < start+length; i++){
                        data = d.read(i);
                        cout << data;
                    }
                } else {
                    string content;
                    int nextIdx = start;
                    for (int i = 0; i < length; i++){
                        data = d.read(nextIdx);
                        nextIdx = data[0];
                        for (int j = 1; j < blockSize; j++){
                            cout << data[j];
                        }
                    }
                }
            } else {
                int idxBlock  = fileData2[1];
                string indices = d.read(idxBlock);
                int idx = 0;
                while (indices[idx] != '\0') {
                    int n = indices[idx] - '0';
                    data = d.read(n);
                    cout << data;
                    idx++;
                }
            }
            return;
        }
        void displayFileTable(){
            string data = d.read(0);
            cout << data;
            return;
        }
        void displayBitmap(){
            string data = d.read(1);
            cout << endl;
            for(int i = 0; i < blockNumber; i++){
                if(i != 0 && (i % 32 == 0)) cout << endl;
                cout << data[i];
            }
            cout << endl;
            return;
        }
        void displayDiskBlock(){
            string data;
            int blockNum;
            cout << "Block Number: ";
            cin >> blockNum;
            cout << endl;
            data = d.read(blockNum);
            cout << data << endl;
            return;
        }
        void copyToReal(){
            string src, dest, data;
            src = getFileName("Copy from: ");
            dest = getFileName("Copy to: ");
            ofstream f(dest, ios::out);
                if (f.is_open()) {
                    int result = searchFile(src, method);
                    if(result == -1){
                        return;
                    }
                    int arrlen = sizeof(fileData1) / sizeof(fileData1[0]);
                    if (arrlen == 0) {
                        return;
                    }
                    if (method == "contiguous" || method == "chained"){
                    int start  = fileData1[1];
                    int length = fileData1[2];
                    if (method == "contiguous"){
                        for (int i = start; i < start+length; i++){
                            data = d.read(i);
                            for (int j = 0; j < blockSize; j++){
                                if (data[j] != '\0'){
                                    f << data[j];
                                }
                            }
                        }
                    } else {
                        string content;
                        int nextIdx = start;
                        for (int i = 0; i < length; i++){
                            data = d.read(nextIdx);
                            nextIdx = data[0];
                            char c;
                            for (int j = 1; j < blockSize; j++){
                                if (data[j] != '\0'){
                                    f << data[j];
                                }
                            }
                        }
                    }
                } else {
                    int idxBlock  = fileData2[1];
                    string indices = d.read(idxBlock);
                    int idx = 0;
                    while (indices[idx] != '\0') {
                        int n = indices[idx] - '0';
                        data = d.read(n);
                        for (int j = 1; j < blockSize; j++){
                            if (data[j] != '\0'){
                                    f << data[j];
                            }
                        }
                        idx++;
                    }
                }
                f.close();
            } else {
                cerr << "Error: File failed to open" << endl;
                return;
            }
            return;
        }
        void copyToSimu(){
            string src, data;
            int blockNum, fileSizeInt;
            src = getFileName("Copy from: ");
            ifstream f(src, ios::binary);
            if (f.is_open()) {
                f.seekg(0, ios::end);
                streampos fileSize = f.tellg();
                fileSizeInt = static_cast<int>(fileSize); 
                f.seekg(0, ios::beg);
                blockNum = ceil(float(fileSizeInt)/blockSize);
                if (blockNum > 10) {
                    cerr << "File too large" << endl; 
                    return;
                }
                //---------------------------------------------------------
                if (method == "contiguous"){
                    string target = "";
                    int counter = 0;
                    int nxtAvailBitIdx, nxtAvailTblIdx;
                    for (int i = 0; i < blockNum; i++){ 
                        target += '0';
                    };
                    data = d.read(1);
                    nxtAvailBitIdx = data.find(target);
                    if (nxtAvailBitIdx == -1){ 
                        cerr << "No available space in the disk." << endl; 
                        return;
                    }

                    for (int i = nxtAvailBitIdx; i < nxtAvailBitIdx+blockNum; i++){
                        data[i] = '1';
                    }
                    d.write(1, data);
                    data = d.read(0);
                    nxtAvailTblIdx = data.find('\0');
                    while(src[counter]!='\0'){
                        data[nxtAvailTblIdx] = src[counter];
                        counter++;
                        nxtAvailTblIdx++;
                    }
                    while(counter < 8){
                        data[nxtAvailTblIdx] = ' ';
                        counter++;
                        nxtAvailTblIdx++;
                    }

                    if (nxtAvailBitIdx >= 100){
                        int hundsPlace = nxtAvailBitIdx / 100;
                        int tensPlace = (nxtAvailBitIdx / 10) % 10;
                        int onePlace =  (nxtAvailBitIdx % 100) % 10;
                        data[nxtAvailTblIdx] = '0' + hundsPlace;
                        data[nxtAvailTblIdx+1] = '0' + tensPlace;
                        data[nxtAvailTblIdx+2] = '0' + onePlace;
                    } else if (100 > nxtAvailBitIdx && nxtAvailBitIdx >= 10){
                        int tensPlace = nxtAvailBitIdx / 10;
                        int onePlace =  nxtAvailBitIdx % 10;
                        data[nxtAvailTblIdx] = ' ';
                        data[nxtAvailTblIdx+1] = '0' + tensPlace;
                        data[nxtAvailTblIdx+2] = '0' + onePlace;
                    } else if (10 > nxtAvailBitIdx && nxtAvailBitIdx >= 0){
                        data[nxtAvailTblIdx] = ' ';
                        data[nxtAvailTblIdx+1] = ' ';
                        data[nxtAvailTblIdx+2] = '0' + nxtAvailBitIdx;
                    }

                    if (blockNum == 10){
                        int tensPlace = blockNum / 10;
                        int onePlace =  blockNum % 10;
                        data[nxtAvailTblIdx+3] = '0' + tensPlace;
                        data[nxtAvailTblIdx+4] = '0' + onePlace;
                    } else {
                        data[nxtAvailTblIdx+3] = ' ';
                        data[nxtAvailTblIdx+4] = '0' + blockNum;
                    }
                    data[nxtAvailTblIdx+5] = '\n';
                    d.write(0, data);

                    char character;
                    for(int i = nxtAvailBitIdx; i < nxtAvailBitIdx+blockNum; i++){
                        data = d.read(i);
                        for (int j = 0; j < blockSize; j++){
                            f.get(character);
                            if (!f.eof()) {
                                data[j] = character;
                            } else {
                                while(j < blockSize){
                                    data[j] = '\0';
                                    j++;
                                }
                                f.close();
                                break;
                            }
                        }
                        d.write(i, data);
                    }
                    cout << endl;
                //---------------------------------------------------------
                } else if (method == "chained") {
                    // find an available space in the disk
                    data = d.read(1);
                    int counter = 0;
                    bool found = false;
                    int nxtAvailTblIdx, nxtAvailBitIdx;
                    int availableIdxs[blockNum];
                    for (int i = 0; i < blockSize; i++){
                        if(data[i] == '0'){
                            availableIdxs[counter] = i;
                            counter++;
                            if (counter == blockNum){
                                found = true;
                                break;
                            }
                        }
                    }
                    if (!found){
                        cerr << "No available space in the disk." << endl;
                        exit(1);
                    }
                    for(int i = 0; i < counter; i++){
                        data[availableIdxs[i]] = '1';
                    }
                    d.write(1, data);
                    
                    // update the file allocation table;
                    data = d.read(0);
                    nxtAvailTblIdx = data.find('\0');
                    counter = 0;
                    while(src[counter]!='\0'){
                        data[nxtAvailTblIdx] = src[counter];
                        counter++;
                        nxtAvailTblIdx++;
                    }
                    while(counter < 8){
                        data[nxtAvailTblIdx] = ' ';
                        counter++;
                        nxtAvailTblIdx++;
                    }

                    nxtAvailBitIdx = availableIdxs[0];
                    if (nxtAvailBitIdx >= 100){
                        int hundsPlace = nxtAvailBitIdx / 100;
                        int tensPlace = (nxtAvailBitIdx / 10) % 10;
                        int onePlace =  (nxtAvailBitIdx % 100) % 10;
                        data[nxtAvailTblIdx] = '0' + hundsPlace;
                        data[nxtAvailTblIdx+1] = '0' + tensPlace;
                        data[nxtAvailTblIdx+2] = '0' + onePlace;
                    } else if (100 > nxtAvailBitIdx && nxtAvailBitIdx >= 10){
                        int tensPlace = nxtAvailBitIdx / 10;
                        int onePlace =  nxtAvailBitIdx % 10;
                        data[nxtAvailTblIdx] = ' ';
                        data[nxtAvailTblIdx+1] = '0' + tensPlace;
                        data[nxtAvailTblIdx+2] = '0' + onePlace;
                    } else if (10 > nxtAvailBitIdx && nxtAvailBitIdx >= 0){
                        data[nxtAvailTblIdx] = ' ';
                        data[nxtAvailTblIdx+1] = ' ';
                        data[nxtAvailTblIdx+2] = '0' + nxtAvailBitIdx;
                    }

                    if (blockNum == 10){
                        int tensPlace = blockNum / 10;
                        int onePlace =  blockNum % 10;
                        data[nxtAvailTblIdx+3] = '0' + tensPlace;
                        data[nxtAvailTblIdx+4] = '0' + onePlace;
                    } else {
                        data[nxtAvailTblIdx+3] = ' ';
                        data[nxtAvailTblIdx+4] = '0' + blockNum;
                    }
                    data[nxtAvailTblIdx+5] = '\n';

                    d.write(0, data);
                    // update the bitmap
                    // write to the disk
                    char character;
                    for (int i = 0; i < blockNum; i++){
                        data = d.read(availableIdxs[i]);
                        if (i+1 != blockNum){
                            data[0] = availableIdxs[i+1];
                        } else {
                            data[0] = availableIdxs[i];
                        }
                        for (int j = 1; j < blockSize; j++){
                            f.get(character);
                            if (!f.eof()) {
                                data[j] = character;
                            } else {
                                while(j < blockSize){
                                    data[j] = '\0';
                                    j++;
                                }
                                f.close();
                                break;
                            }
                        }
                        d.write(availableIdxs[i], data);
                    }
                } else {
                    // find an available space in the disk
                    data = d.read(1);
                    int counter = 0;
                    bool found = false;
                    int nxtAvailTblIdx, nxtAvailBitIdx;
                    int availableIdxs[blockNum+1];
                    for (int i = 0; i < blockSize+1; i++){
                        if(data[i] == '0'){
                            availableIdxs[counter] = i;
                            counter++;
                            if (counter == blockNum+1){
                                found = true;
                                break;
                            }
                        }
                    }
                    if (!found){
                        cerr << "No available space in the disk." << endl;
                        exit(1);
                    }
                    for(int i = 0; i < counter; i++){
                        data[availableIdxs[i]] = '1';
                    }
                    d.write(1, data);

                    data = d.read(0);
                    nxtAvailTblIdx = data.find('\0');

                    counter = 0;
                    while(src[counter] != '\0') {
                        data[nxtAvailTblIdx] = src[counter];
                        nxtAvailTblIdx++;
                        counter++;
                    }
                    while(counter < 8){
                        data[nxtAvailTblIdx] = ' ';
                        counter++;
                        nxtAvailTblIdx++;
                    }
                    nxtAvailBitIdx = availableIdxs[0];
                    if (nxtAvailBitIdx >= 100){
                        int hundsPlace = nxtAvailBitIdx / 100;
                        int tensPlace = (nxtAvailBitIdx / 10) % 10;
                        int onePlace =  (nxtAvailBitIdx % 100) % 10;
                        data[nxtAvailTblIdx] = '0' + hundsPlace;
                        data[nxtAvailTblIdx+1] = '0' + tensPlace;
                        data[nxtAvailTblIdx+2] = '0' + onePlace;
                    } else if (100 > nxtAvailBitIdx && nxtAvailBitIdx >= 10){
                        int tensPlace = nxtAvailBitIdx / 10;
                        int onePlace =  nxtAvailBitIdx % 10;
                        data[nxtAvailTblIdx] = ' ';
                        data[nxtAvailTblIdx+1] = '0' + tensPlace;
                        data[nxtAvailTblIdx+2] = '0' + onePlace;
                    } else if (10 > nxtAvailBitIdx && nxtAvailBitIdx >= 0){
                        data[nxtAvailTblIdx] = ' ';
                        data[nxtAvailTblIdx+1] = ' ';
                        data[nxtAvailTblIdx+2] = '0' + nxtAvailBitIdx;
                    }
                    data[nxtAvailTblIdx+3] = '\n';
                    d.write(0, data);

                    // write the index block
                    int len = sizeof(availableIdxs) / sizeof(availableIdxs[0]);
                    data = d.read(nxtAvailBitIdx);
                    int cnt = 0;
                    for (int i = 1; i < len; i++){
                        if(availableIdxs[i] < 10){
                            char c = '0' + availableIdxs[i];
                            data[cnt] = c;
                            cnt++;
                            data[cnt] = ' ';
                            cnt++;
                        } else if(10 <= availableIdxs[i] && availableIdxs[i] < 100){
                            int tensPlace = availableIdxs[i] / 10;
                            int onePlace =  availableIdxs[i] % 10;
                            char c = '0' + tensPlace;
                            data[cnt] = c;
                            cnt++;
                            c = '0' + onePlace;
                            data[cnt] = c;
                            cnt++;
                            data[cnt] = ' ';
                            cnt++;
                        } else if(100 <= availableIdxs[i]) {
                            int hundsPlace = availableIdxs[i] / 100;
                            int tensPlace = (availableIdxs[i] / 10) % 10;
                            int onePlace =  (availableIdxs[i] % 100) % 10;
                            char c = '0' + hundsPlace;
                            data[cnt] = c;
                            cnt++;
                            c = '0' + tensPlace;
                            data[cnt] = c;
                            cnt++;
                            c = '0' + onePlace;
                            data[cnt] = c;
                            cnt++;
                            data[cnt] = ' ';
                            cnt++;
                        }
                        
                    }
                    // data[len-1] = '\0';
                    while(cnt < blockSize){
                        data[cnt] = '\0';
                        cnt++;
                    }
                    d.write(nxtAvailBitIdx, data);

                    char character;
                    for (int i = 1; i <= blockNum; i++){
                        data = d.read(availableIdxs[i]);
                        for (int j = 1; j < blockSize; j++){
                            f.get(character);
                            if (!f.eof()) {
                                data[j] = character;
                            } else {
                                while(j < blockSize){
                                    data[j] = '\0';
                                    j++;
                                }
                                f.close();
                                break;
                            }
                        }
                        d.write(availableIdxs[i], data);
                    }
                }
            } else {
                cerr << "Error: File failed to open" << endl;
                return;
            }
            cout << "File " << src << " copied" << endl;
            return;
        }
        void deleteFile(){
            string fn;
            string data;
            int fileIdx, startIdx, length;
            fn = getFileName("File name: ");
            int result = searchFile(fn, method);
            if(result == -1){
                return;
            }
            fileIdx = fileData1[0];
            if (method == "contiguous" || method == "chained"){
                // delete the file from the file allocation table
                data = d.read(0);
                for(int i = fileIdx; i < fileIdx+13; i++){
                    data[i] = '\0';
                }
                d.write(0, data);
                // update the bitmap
                data = d.read(1);
                startIdx = fileData1[1];
                length = fileData1[2];
                if (method == "contiguous"){
                    for (int i = startIdx; i < startIdx+length; i++){
                        data[i]='0';
                    }
                    d.write(1, data);
                } else {
                    int nextIdx = startIdx;
                    for (int i = 0; i < length; i++){
                        string data2 = d.read(nextIdx);
                        data[nextIdx] = '0';
                        nextIdx = data2[0];
                    }
                    d.write(1, data);
                }
            } else {
                // update the bitmap
                data = d.read(1);
                int idxBlock  = fileData2[1];
                data[idxBlock] = '0';
                string indices = d.read(idxBlock);
                int idx = 0;
                while (indices[idx] != '\0') {
                    int n = indices[idx] - '0';
                    data[n] = '0';
                    idx++;
                }
                d.write(1, data);
                // delete the file from the file allocation table
                data = d.read(0);
                for(int i = fileIdx; i < fileIdx+11; i++){
                    data[i] = '\0';
                }
                d.write(0, data);
            }
            return;
        }
};
