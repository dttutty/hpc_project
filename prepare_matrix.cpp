#include "lib/save_and_load_matrix.h"
#include <iostream>

int main(int argc, char* argv[]){
    if (argc != 5){
        std::cerr << "Usage: " << argv[0] << " <rows> <cols> <sparse> <filename>" << std::endl;
        return;
    }
    int n = std::stoi(argv[1]);
    float sparse = std::stof(argv[2]);
    const char* filename = argv[3];
    save_matrix_file(n, sparse, filename);
    return 0;
}
