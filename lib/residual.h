#pragma once

#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

float get_residual(std::vector<std::vector<float>> A, std::vector<float> x, std::vector<float> b);
float get_residual_omp(std::vector<std::vector<float>> A, std::vector<float> x, std::vector<float> b);
