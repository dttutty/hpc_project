#pragma once
#include <iostream>
#include <chrono>
#include <omp.h>
#include <vector>
#include <random>
#include <algorithm>
#include "gen_random.h"
#include "residual.h"
#include "print_time.h"

std::vector<float> jacobi(std::vector<std::vector<float>> A, std::vector<float> b, int max_iter, float tol);
std::vector<float> jacobi_omp(std::vector<std::vector<float>> A, std::vector<float> b, int max_iter, float tol);
