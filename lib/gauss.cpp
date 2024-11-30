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
#include "gauss.h"
#include "coloring.h"

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
//     auto colors = fratarcangeli(A); // get coloring
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

