#include "gauss.h"

// Gauss-Seidel method
std::vector<float> gauss_seidel(std::vector<std::vector<float>> A, std::vector<float> b, int max_iter, float tol) {
    int n = A.size();
    std::vector<float> x(n, 0);
    std::vector<float> residual(max_iter * n, 0);
    int final_iter = 0;
    int final_residual_index = 0;
    for (int iter = 0; iter < max_iter; iter++) {
        final_iter = iter + 1;
        bool stop = false;
        for (int i = 0; i < n; i++) {
            float sum = 0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += A[i][j] * x[j];
                }
            }
            x[i] = (b[i] - sum) / A[i][i];
            final_residual_index = iter * n + i;
            if (final_residual_index % 100 == 0) {
                residual[final_residual_index] = get_residual_omp(A, x, b);
                if (residual[final_residual_index] < tol) {
                    stop = true;
                    break;
                }
            }
        }
        if (stop) {
            break;
        }
    }
    std::cout << "Total iterations: <=" << final_iter << std::endl;
    std::cout << "Final residual: " << residual[final_residual_index] << std::endl;
    //show all residuals
    // for (int i = 0; i <= final_iter; i++) {
    //     std::cout << "gauss residuals " << i << ": " << residual[i] << std::endl;
    // }
    return x;
}

// Gauss-Seidel method with OpenMP
std::vector<float> gauss_seidel_omp(std::vector<std::vector<float>> A, std::vector<float> b, int max_iter, float tol) {
    int n = A.size();
    std::vector<float> x(n, 0);
    std::vector<float> residual(max_iter * n, 0);
    int final_iter = 0;
    int final_residual_index = 0;
    std::cout << "Start coloring" << std::endl;
    auto partitions = greedy_coloring(A); // get coloring
    auto partitions_size = partitions.size();
    std::cout << "Partitions number: " << partitions_size << std::endl;    //print partitions number
    std::cout << "Start CAL_OMP" << std::endl;
    for (int iter = 0; iter < max_iter; iter++) {
        final_iter = iter + 1;
        bool stop = false;
        std::size_t current_partition_index = 0;
        for (auto partition : partitions) {
            current_partition_index++;
#pragma omp parallel for
            for (int i : partition) {
                float sum = 0;
                for (int j = 0; j < n; j++) {
                    if (j != i) {
                        sum += A[i][j] * x[j];
                    }
                }
                x[i] = (b[i] - sum) / A[i][i];
            }
            final_residual_index = iter * partitions_size + current_partition_index;
            if (final_residual_index % 100 == 0) {
                residual[final_residual_index] = get_residual_omp(A, x, b);
                if (residual[final_residual_index] < tol) {
                    stop = true;
                    break;
                }
            }
        }

        if (stop) {
            break;
        }
    }
    std::cout << "Total iterations: <=" << final_iter << std::endl;
    std::cout << "Final residual: " << residual[final_residual_index] << std::endl;
    //show all residuals
    // for (int i = 0; i <= final_residual_index; i++) {
    //     std::cout << "Residual " << i << ": " << residual[i] << std::endl;
    // }
    return x;
}

