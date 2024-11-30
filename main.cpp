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


int main(int argc, char* argv[]){
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <matrix_size>" << std::endl;
        return 1;
    }

    int n = std::stoi(argv[1]);
    int max_iter = 1000;
    float tol = 1e-2;
    float sparse = 0.0;
    auto A = generate_matrix(n, sparse);
    // check if thematrix is diagonally dominant
    std::cout << "Is the matrix diagonally dominant? " << is_diagonally_dominant(A) << std::endl;
    // Ensure the matrix is diagonally dominant
    while (!is_diagonally_dominant(A)) {
        A = generate_matrix(n, sparse);
    }
    auto b = generate_vector(n);

    auto start = std::chrono::high_resolution_clock::now();
    auto x = jacobi(A, b, max_iter, tol);
    std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::high_resolution_clock::duration> end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken for Jacobi method: " << elapsed.count() << " s" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    x = jacobi_cal_omp(A, b, max_iter, tol);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken for Jacobi method with cal_omp: " << elapsed.count() << " s" << std::endl;


    start = std::chrono::high_resolution_clock::now();
    x = jacobi_cal_omp_res_omp(A, b, max_iter, tol);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken for Jacobi method with cal_omp, res_omp: " << elapsed.count() << " s" << std::endl;



    start = std::chrono::high_resolution_clock::now();
    x = gauss_seidel(A, b, max_iter, tol);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken for Gauss-Seidel method: " << elapsed.count() << " s" << std::endl;

    // start = std::chrono::high_resolution_clock::now();
    // auto x_omp = gauss_seidel_omp(A, b, max_iter, tol);
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // std::cout << "Elapsed time for Gauss-Seidel method with OpenMP: " << elapsed.count() << " s" << std::endl;
    return 0;
}
