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
std::vector<float> gauss_seidel(std::vector<std::vector<float>> A, std::vector<float> b, int max_iter, float tol);

// Gauss-Seidel method with OpenMP
std::vector<float> gauss_seidel_omp(std::vector<std::vector<float>> A, std::vector<float> b, int max_iter, float tol);
