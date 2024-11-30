#include <iostream>
#include <chrono>
#include <omp.h>
#include <vector>
#include <random>
#include <algorithm>
#include "gen_random.h"
#include "residual.h"
#include "jacobi.h"
#include "gauss.h"

auto measure_time = [](auto func, const auto& A, const auto& b, int max_iter, float tol, const std::string& method_name) {
    auto start = std::chrono::high_resolution_clock::now();
    auto x = func(A, b, max_iter, tol);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken for " << method_name << ": " << elapsed.count() << " s" << std::endl;
};

int main(int argc, char* argv[]){
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <matrix_size> <sparse_ratio>" << std::endl;
        return 1;
    }

    int n = std::stoi(argv[1]);
    float sparse = std::stof(argv[2]);
    int max_iter = 1000;
    float tol = 1e-2;
    auto A = generate_matrix(n, sparse);
    // check if thematrix is diagonally dominant
    std::cout << "Is the matrix diagonally dominant? " << is_diagonally_dominant(A) << std::endl;
    auto b = generate_vector(n);

    std::cout << "======================Jacobi======================" << std::endl;
    measure_time(jacobi, A, b, max_iter, tol, "Jacobi method");
    measure_time(jacobi_cal_omp, A, b, max_iter, tol, "Jacobi method with cal_omp");
    measure_time(jacobi_cal_omp_res_omp, A, b, max_iter, tol, "Jacobi method with cal_omp, res_omp");

    std::cout << "===================Gauss-Seidel===================" << std::endl;
    measure_time(gauss_seidel, A, b, max_iter, tol, "Gauss-Seidel method");
    measure_time(gauss_seidel_omp, A, b, max_iter, tol, "Gauss-Seidel omp");

    return 0;
}
