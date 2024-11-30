#include "gen_random.h"


// //generate a random matrix with a sparse percentage
// std::vector<std::vector<float>> generate_matrix(int n, float sparse){
//     std::vector<std::vector<float>> matrix(n, std::vector<float>(n));
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_real_distribution<> dis(0, 1);
//     for (int i = 0; i < n; i++){
//         std::generate(matrix[i].begin(), matrix[i].end(), [&](){
//             return dis(gen) < sparse ? 0.0f : dis(gen);
//         });
//     } 
//     return matrix;
// }

// //generate a random vector with a sparse percentage
// std::vector<float> generate_vector(int n){
//     std::vector<float> b(n);
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_real_distribution<> dis(0, 1);
//     std::generate(b.begin(), b.end(), [&](){
//         return dis(gen);
//     });
//     return b;
// }
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

// Generate a random matrix with a sparse percentage, ensuring a well-conditioned matrix
std::vector<std::vector<float>> generate_matrix(int n, float sparse) {
    std::vector<std::vector<float>> matrix(n, std::vector<float>(n, 0.0f));

    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.1, 1.0); // Avoid zero for better conditioning

    // Ensure diagonal elements are large enough to help the matrix be well-conditioned
    for (int i = 0; i < n; i++) {
        // Generate non-diagonal elements
        for (int j = 0; j < n; j++) {
            if (i != j) {
                matrix[i][j] = dis(gen) < sparse ? 0.0f : dis(gen); // Add non-zero elements based on sparse rate
            }
        }

        // Generate diagonal elements, making them larger to ensure diagonal dominance
        float diagonal_value = dis(gen) * 10.0f; // Diagonal elements are scaled up by a factor of 10
        matrix[i][i] = diagonal_value;
    }

    // Optional: Normalize matrix to ensure it's positive definite
    // By adjusting the diagonal values after matrix generation, we make sure it's positive definite
    // If matrix is not diagonally dominant enough, adjust the diagonal elements again
    for (int i = 0; i < n; i++) {
        float row_sum = 0.0f;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                row_sum += std::abs(matrix[i][j]);
            }
        }
        if (std::abs(matrix[i][i]) <= row_sum) {
            matrix[i][i] = row_sum + 1.0f;  // Adjust diagonal element if it's not sufficiently large
        }
    }

    return matrix;
}

// Generate a random vector for right-hand side b
std::vector<float> generate_vector(int n) {
    std::vector<float> b(n);

    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.1, 1.0); // Avoid zero values

    std::generate(b.begin(), b.end(), [&](){
        return dis(gen);
    });

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
