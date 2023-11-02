class Disk {
private:
    int disk[256][512];
public:
    Disk(){
        for (int i = 0; i < sizeof(disk[0]); i++){
            disk[0][i] = 0;
        }
    }

    void write(int blockAdd, int offset, int val){
        if (blockAdd > 255 || blockAdd < 0 || offset > 511 || offset < 0){
            cerr << "Invalid address access. Address: disk[" + to_string(blockAdd) + "][" + to_string(blockAdd) + "] does not exist."  << endl;
        }
        disk[blockAdd][blockAdd] = val;
        return;
    }

    int read(int blockAdd, int offset){
        if (blockAdd > 255 || blockAdd < 0 || offset > 511 || offset < 0){
            cerr << "Invalid address access. Address: disk[" + to_string(blockAdd) + "][" + to_string(blockAdd) + "] does not exist."  << endl;
        }
        return disk[blockAdd][offset];
    }
};