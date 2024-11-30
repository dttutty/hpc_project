#include <iostream>
#include <cmath>
#include <chrono>

#include <omp.h>
#include <vector>
#include <random>
#include <algorithm>
#include <vector>
#include "gen_random.h"
#include "residual.h"

// Gauss-Seidel method
std::vector<float> gauss_seidel(std::vector<std::vector<float>> A, std::vector<float> b, int max_iter, float tol){
    int n = A.size();
    std::vector<float> x(n, 0);
    std::vector<float> residual(max_iter, 0);
    int final_iter = 0;
    for (int iter = 0; iter < max_iter; iter++){
        final_iter = iter + 1;
        for (int i = 0; i < n; i++){
            float sum = 0;
            for (int j = 0; j < n; j++){
                if (j != i){
                    sum += A[i][j] * x[j];
                }
            }
            x[i] = (b[i] - sum) / A[i][i];
        }
        residual[iter] = get_residual(A, x, b);
        if (residual[iter] < tol){
            break;
        }
    }
    std::cout << "Total iterations: " << final_iter << std::endl;
    //show last 1 residuals
    for (int i = final_iter - 1; i < final_iter; i++){
        std::cout << "Residual " << i << ": " << residual[i] << std::endl;
    }
    return x;
}

// // Gauss-Seidel method with OpenMP
// std::vector<float> gauss_seidel_omp(std::vector<std::vector<float>> A, std::vector<float> b, int max_iter, float tol){
//     int n = A.size();
//     std::vector<float> x(n, 0);
//     std::vector<float> x_new(n, 0);
//     std::vector<float> residual(max_iter, 0);
//     for (int iter = 0; iter < max_iter; iter++){
//         #pragma omp parallel for
//         for (int i = 0; i < n; i++){
//             float sum = 0;
//             for (int j = 0; j < n; j++){
//                 if (j != i){
//                     sum += A[i][j] * x[j];
//                 }
//             }
//             x_new[i] = (b[i] - sum) / A[i][i];
//         }
//         x = x_new;
//         residual[iter] = get_residual(A, x, b);
//         if (residual[iter] < tol){
//             break;
//         }
//     }
//     return x;
// }

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
    auto b = generate_vector(n);
    auto start = std::chrono::high_resolution_clock::now();
    auto x = gauss_seidel(A, b, max_iter, tol);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time for Gauss-Seidel method: " << elapsed.count() << " s" << std::endl;

    // start = std::chrono::high_resolution_clock::now();
    // auto x_omp = gauss_seidel_omp(A, b, max_iter, tol);
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // std::cout << "Elapsed time for Gauss-Seidel method with OpenMP: " << elapsed.count() << " s" << std::endl;
    return 0;
}
