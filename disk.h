using namespace std;

const int num_blocks = 256;
const int block_size = 512;

class Disk {
public:
    Disk(){
        // declare a disk array with initial value '\0's
        disk[num_blocks][block_size] = {};

        // initialize the bit map
        // the first and second bit will always be occupied by the table allocation and bit map
        for (int i = 0; i < num_blocks; i++) {
            if (i == 0 || i == 1){
                disk[1][i] = '1';
            } else {
                disk[1][i] = '0';
            } 
        }
    }

    bool write(int block_num, const string& data) {
        // reject writing if block_num is invlaid or passed data is too large
        if (block_num < 0 || block_num >= num_blocks || data.length() > block_size) {
            cerr << "Block does not exist or data too large." << endl;
            return false;
        }

        // write to disk character by character
        for (int j = 0; j < block_size; j++) {
            disk[block_num][j] = data[j];
        }

        return true;
    }

    string read(int block_num) {
        // return an empty string if the block_num is invalid
        if (block_num < 0 || block_num >= num_blocks) {
            cerr << "Block does not exist." << endl;
            return "";
        }

        string data;
        for (int j = 0; j < block_size; j++) {
            data += disk[block_num][j];
        }
        return data;
    }

private:
    char disk[num_blocks][block_size] = {};
};

