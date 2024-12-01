#include "gen_random.h"
#include <omp.h>
#include <vector>
#include <random>
#include <cmath>


// Generate a random matrix with a sparse percentage, ensuring a well-conditioned matrix
std::vector<std::vector<float>> generate_matrix(int n, float sparse) {
    std::vector<std::vector<float>> matrix(n, std::vector<float>(n, 0.0f));

    // Random number generator
    std::random_device rd;
    std::uniform_real_distribution<> dis(0.1, 1.0);

#pragma omp parallel
    {
        // use different random seed for each thread
        std::mt19937 gen(rd() ^ omp_get_thread_num());

        // generate random matrix parallelly
#pragma omp for
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    matrix[i][j] = dis(gen) < sparse ? 0.0f : dis(gen);
                }
            }
            matrix[i][i] = dis(gen) * 10.0f; // make sure the matrix is well-conditioned
        }

        // adjust the diagonal elements to ensure the matrix is diagonally dominant
#pragma omp for
        for (int i = 0; i < n; i++) {
            float row_sum = 0.0f;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    row_sum += std::abs(matrix[i][j]);
                }
            }
            if (std::abs(matrix[i][i]) <= row_sum) {
                matrix[i][i] = row_sum + 1.0f; // adjust the diagonal element
            }
        }
    }

    return matrix;
}


// Generate a random vector for b
std::vector<float> generate_vector(int n) {
    std::vector<float> b(n);

    // Random number generator
    std::random_device rd;
    std::uniform_real_distribution<> dis(0.1, 1.0);

#pragma omp parallel
    {

        std::mt19937 gen(rd() ^ omp_get_thread_num());

#pragma omp for
        for (int i = 0; i < n; ++i) {
            b[i] = dis(gen);
        }
    }

    return b;
}


bool is_diagonally_dominant(const std::vector<std::vector<float>>& A) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        float sum = 0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                sum += std::abs(A[i][j]);
            }
        }
        if (std::abs(A[i][i]) <= sum) {
            return false;
        }
    }
    return true;
}
