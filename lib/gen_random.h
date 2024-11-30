#include <vector>
#include <random>
#include <algorithm>

std::vector<std::vector<float>> generate_matrix(int n, float sparse);
std::vector<float> generate_vector(int n);
bool is_diagonally_dominant(const std::vector<std::vector<float>>& A);
