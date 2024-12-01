#include <iostream>
#include <chrono>
#include <omp.h>
#include <iomanip>
#include <vector>
#include <random>
#include <algorithm>
#include "gen_random.h"
#include "residual.h"
#include "jacobi.h"
#include "gauss.h"
#include "print_time.h"
#include <functional>

void measure_execution_time(std::function<void()> func, std::string method = "") {

    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << method << " execution time: " << duration << " ms" << std::endl;
}

int main(int argc, char* argv[]) {
    // usage: ./main <flags> <matrix_size> <sparse_ratio> [-v]
    // flags: 4-digit string only containing 0s and 1s, each digit corresponds to a method
    // methods: jacobi, jacobi_omp, gauss_seidel, gauss_seidel_omp
    // example: 1010 means to run jacobi and gauss_seidel
    std::string t0;
    bool verbose = false;
    if (argc != 4 && argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <flags> <matrix_size> <sparse_ratio> [-v]" << std::endl;
        return 1;
    }

    if (argc == 5 && std::string(argv[4]) == "-v") {
        verbose = true;
    }

    std::string flags = argv[1];
    if (flags.length() != 4 || flags.find_first_not_of("01") != std::string::npos) {
        std::cerr << "Flags must be a 4-digit string containing only 0s and 1s." << std::endl;
        return 1;
    }

    bool j = flags[0] == '1';
    bool k = flags[1] == '1';
    bool g = flags[2] == '1';
    bool h = flags[3] == '1';

    int n = std::stoi(argv[2]);
    float sparse = std::stof(argv[3]);
    int max_iter = 10000;
    float tol = 1e-2;
    auto A = generate_matrix(n, sparse);
    // check if the matrix is diagonally dominant
    if (verbose) {
        std::cout << "Is the matrix diagonally dominant? " << is_diagonally_dominant(A) << std::endl;
    }
    auto b = generate_vector(n);

    std::cout << "======================Jacobi======================" << std::endl;
    if (j) { measure_execution_time([&]() { jacobi(A, b, max_iter, tol); }, "jacobi"); }
    if (k) { measure_execution_time([&]() { jacobi_omp(A, b, max_iter, tol); }, "jacobi_omp"); }
    std::cout << "===================Gauss-Seidel===================" << std::endl;
    if (g) { measure_execution_time([&]() { gauss_seidel(A, b, max_iter, tol); }, "gauss_seidel"); }
    if (h) { measure_execution_time([&]() { gauss_seidel_omp(A, b, max_iter, tol); }, "gauss_seidel_omp"); }

    return 0;
}
