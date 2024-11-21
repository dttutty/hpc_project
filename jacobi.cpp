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


float calculate_residual_omp(std::vector<std::vector<float>> A, std::vector<float> x, std::vector<float> b) {
    int n = A.size();
    std::vector<float> Ax(n, 0);
    std::vector<float> x_copy = x;  // 创建 x 的副本
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        float sum = 0;
        for (int j = 0; j < n; j++) {
            Ax[i] += A[i][j] * x[j];
        }
    }
    float residual = 0;
    #pragma omp parallel for reduction(+:residual)
    for (int i = 0; i < n; i++) {
        residual += (Ax[i] - b[i]) * (Ax[i] - b[i]);
    }
    return sqrt(residual);
}

// Jacobi method
std::vector<float> jacobi(std::vector<std::vector<float>> A, std::vector<float> b, int max_iter, float tol){
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

// Jacobi method with OpenMP, calculate_residual_omp
std::vector<float> jacobi_omp(std::vector<std::vector<float>> A, std::vector<float> b, int max_iter, float tol){
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
        residual[iter] = calculate_residual_omp(A, x, b);
        if (residual[iter] < tol){
            break;
        }
    }
    return x;
}

std::vector<float> jacobi_omp_copy_x(std::vector<std::vector<float>> A, std::vector<float> b, int max_iter, float tol) {
    int n = A.size();
    std::vector<float> x(n, 0);
    std::vector<float> x_new(n, 0);
    std::vector<float> *x_curr = &x, *x_next = &x_new;
    for (int iter = 0; iter < max_iter; iter++) {
        #pragma omp parallel for
        for (int i = 0; i < n; i++) {
            float sum = 0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += A[i][j] * (*x_curr)[j];
                }
            }
            (*x_next)[i] = (b[i] - sum) / A[i][i];
        }
        std::swap(x_curr, x_next);  // 交换指针，无需拷贝

        // 并行化残差计算
        float residual = calculate_residual(A, x, b);
        if (residual < tol) {
            break;
        }
    }
    return x;
}


// for 1000*1000, calculate_residual_omp is faster than calculate_residual: 11.91s vs 2.59ms
// Jacobi method with OpenMP with calculate_residual
std::vector<float> jacobi_omp_1(std::vector<std::vector<float>> A, std::vector<float> b, int max_iter, float tol){
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
    int n = 2000;
    int max_iter = 1000;
    float tol = 1e-6;
    auto A = generate_matrix(n, n);
    auto b = generate_vector(n);

    auto start = std::chrono::high_resolution_clock::now();
    auto x = jacobi(A, b, max_iter, tol);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken for Jacobi method: " << elapsed.count() << " s" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    x = jacobi_omp_1(A, b, max_iter, tol);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken for Jacobi method with OpenMP with calculate_residual: " << elapsed.count() << " s" << std::endl;


    start = std::chrono::high_resolution_clock::now();
    x = jacobi_omp(A, b, max_iter, tol);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken for Jacobi method with OpenMP with calculate_residual_omp: " << elapsed.count() << " s" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    x = jacobi_omp_copy_x(A, b, max_iter, tol);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken for Jacobi method with OpenMP with calculate_residual_omp and copy_x: " << elapsed.count() << " s" << std::endl;

    return 0;
}

