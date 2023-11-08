using namespace std;

const int num_blocks = 256;
const int block_size = 512;

class Disk {
public:
    Disk(){
        disk[num_blocks][block_size] = {};
        for (int i = 0; i < num_blocks; i++) {
            if (i == 0 || i == 1){
                disk[1][i] = '1';
            } else {
                disk[1][i] = '0';
            } 
        }
    }
    bool write(int block_num, const string& data) {
        if (block_num < 0 || block_num >= num_blocks || data.length() > block_size) {
            return false;
        }
        for (int j = 0; j < block_size; j++) {
            disk[block_num][j] = data[j];
        }
        return true;
    }

    string read(int block_num) {
        if (block_num < 0 || block_num >= num_blocks) {
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

