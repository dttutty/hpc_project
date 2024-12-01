#include "residual.h"
#include "print_time.h"

// calculate the residual = A * x - b
float get_residual(std::vector<std::vector<float>> A, std::vector<float> x, std::vector<float> b) {


    int n = A.size();

    float max_A = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            max_A = std::max(max_A, std::abs(A[i][j]));
        }
    }
    // std::cout << "Max value in A: " << max_A << std::endl;


    std::vector<float> Ax(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Ax[i] += A[i][j] * x[j];
        }
    }
    float residual = 0;
    for (int i = 0; i < n; i++) {
        residual += (Ax[i] - b[i]) * (Ax[i] - b[i]);
    }
    // std::cout << "Residual: " << std::sqrt(residual) << std::endl;
    return std::sqrt(residual);
}

float get_residual_omp(std::vector<std::vector<float>> A, std::vector<float> x, std::vector<float> b) {
    int n = A.size();
    std::vector<float> Ax(n, 0);
    std::vector<float> x_copy = x;
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
    return std::sqrt(residual);
}
