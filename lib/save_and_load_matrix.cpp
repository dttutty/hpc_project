#include "gen_random.h"
#include <vector>
#include <iostream>

// generate a random matrix and save it to a file
void save_matrix_file(int n, float sparse, const char* filename){
    auto matrix = generate_matrix(n, sparse);
    FILE* fp = fopen(filename, "w");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            fprintf(fp, "%f ", matrix[i][j]);
        }
        fprintf(fp, "\n");
    }
}

void load_matrix_file(const char* filename, std::vector<std::vector<float>>& matrix){
    FILE* fp = fopen(filename, "r");
    if (fp == NULL){
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return;
    }
    float val;
    while (fscanf(fp, "%f", &val) != EOF){
        matrix.back().push_back(val);
        char c = fgetc(fp);
        if (c == '\n'){
            matrix.push_back(std::vector<float>());
        }
    }
    fclose(fp);
    matrix.pop_back();
}   
