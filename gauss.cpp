#include <iostream>
#include <cmath>
#include <chrono>

# include<omp.h>
#include <vector>
#include <random>
#include <algorithm>
#include <vector>

// generate a random matrix
std::vector<std::vector<float>> generate_matrix(int rows, int cols){
    std::vector<std::vector<float>> matrix(rows, std::vector<float>(cols));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    for (int i = 0; i < rows; i++){
        std::generate(matrix[i].begin(), matrix[i].end(), [&](){return dis(gen);});
    } 
    return matrix;
}

// generate a random vector
std::vector<float> generate_vector(int n){
    std::vector<float> b(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    std::generate(b.begin(), b.end(), [&](){return dis(gen);});
    return b;
}

// calculate the residual
float calculate_residual(std::vector<std::vector<float>> A, std::vector<float> x, std::vector<float> b){
    int n = A.size();
    std::vector<float> Ax(n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            Ax[i] += A[i][j] * x[j];
        }
    }
    float residual = 0;
    for (int i = 0; i < n; i++){
        residual += (Ax[i] - b[i]) * (Ax[i] - b[i]);
    }
    return sqrt(residual);
}

// Gauss-Seidel method
std::vector<float> gauss_seidel(std::vector<std::vector<float>> A, std::vector<float> b, int max_iter, float tol){
    int n = A.size();
    std::vector<float> x(n, 0);
    std::vector<float> x_new(n, 0);
    std::vector<float> residual(max_iter, 0);
    for (int iter = 0; iter < max_iter; iter++){
        for (int i = 0; i < n; i++){
            float sum = 0;
            for (int j = 0; j < n; j++){
                if (j != i){
                    sum += A[i][j] * x[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }
        x = x_new;
        residual[iter] = calculate_residual(A, x, b);
        if (residual[iter] < tol){
            break;
        }
    }
    return x;
}

// Gauss-Seidel method with OpenMP
std::vector<float> gauss_seidel_omp(std::vector<std::vector<float>> A, std::vector<float> b, int max_iter, float tol){
    int n = A.size();
    std::vector<float> x(n, 0);
    std::vector<float> x_new(n, 0);
    std::vector<float> residual(max_iter, 0);
    for (int iter = 0; iter < max_iter; iter++){
        #pragma omp parallel for
        for (int i = 0; i < n; i++){
            float sum = 0;
            for (int j = 0; j < n; j++){
                if (j != i){
                    sum += A[i][j] * x[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }
        x = x_new;
        residual[iter] = calculate_residual(A, x, b);
        if (residual[iter] < tol){
            break;
        }
    }
    return x;
}

int main(){
    int n = 1000;
    int max_iter = 1000;
    float tol = 1e-6;
    auto A = generate_matrix(n, n);
    auto b = generate_vector(n);
    auto start = std::chrono::high_resolution_clock::now();
    auto x = gauss_seidel(A, b, max_iter, tol);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time for Gauss-Seidel method: " << elapsed.count() << " s" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    auto x_omp = gauss_seidel_omp(A, b, max_iter, tol);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Elapsed time for Gauss-Seidel method with OpenMP: " << elapsed.count() << " s" << std::endl;
    return 0;
}
