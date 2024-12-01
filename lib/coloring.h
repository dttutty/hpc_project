#pragma once

#include <set>
#include <cmath>
#include <iostream>
#include <array>
#include <vector>
#include <numeric>
#include <algorithm>

typedef std::vector<int> Partition;
typedef const std::vector<std::vector<float>> Matrix;

std::vector<std::vector<int>> greedy_coloring(const Matrix& A);
