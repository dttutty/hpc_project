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

void measure_execution_time(std::function<void()> func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Execution time: " << duration << " ms" << std::endl;
}

int main(int argc, char* argv[]) {
    std::string t0;
    bool verbose = false;
    if (argc != 3 && argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <matrix_size> <sparse_ratio> [-v]" << std::endl;
        return 1;
    }

    if (argc == 4 && std::string(argv[3]) == "-v") {
        verbose = true;
    }

    int n = std::stoi(argv[1]);
    float sparse = std::stof(argv[2]);
    int max_iter = 1000;
    float tol = 1e-2;
    auto A = generate_matrix(n, sparse);
    // check if the matrix is diagonally dominant
    if (verbose) {
        std::cout << "Is the matrix diagonally dominant? " << is_diagonally_dominant(A) << std::endl;
    }
    auto b = generate_vector(n);

    std::cout << "======================Jacobi======================" << std::endl;
    // t0 = get_current_time(verbose);
    // jacobi(A, b, max_iter, tol);
    // t0 = get_current_time(verbose);
    // jacobi_cal_omp(A, b, max_iter, tol);
    // t0 = get_current_time(verbose);
    // jacobi_cal_omp_res_omp(A, b, max_iter, tol);
    // t0 = get_current_time(verbose);
    std::cout << "===================Gauss-Seidel===================" << std::endl;
    t0 = get_current_time(verbose);
    // measure_execution_time([&]() { gauss_seidel(A, b, max_iter, tol); });
    t0 = get_current_time(verbose);
    measure_execution_time([&]() { gauss_seidel_omp(A, b, max_iter, tol); });
    t0 = get_current_time(verbose);

    return 0;
}
