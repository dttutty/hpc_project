#pragma once

#include <cmath>
#include <iostream>
#include "coloring.h"
#include "gen_random.h"
#include "residual.h"
#include "print_time.h"
#include <algorithm>
#include <chrono>
#include <omp.h>
#include <random>
#include <vector>

// Gauss-Seidel method
std::vector<float> gauss_seidel(std::vector<std::vector<float>> A,
    std::vector<float> b, int max_iter, float tol);

// Gauss-Seidel method with OpenMP
std::vector<float> gauss_seidel_omp(std::vector<std::vector<float>> A,
    std::vector<float> b, int max_iter,
    float tol);
