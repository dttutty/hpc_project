#include <iostream>
#include <vector>

std::vector<std::vector<float>> generate_matrix(int rows, int cols) {
    std::vector<std::vector<float>> matrix(rows, std::vector<float>(cols));
    std::cout << "Address of matrix (stack): " << &matrix << std::endl;
    std::cout << "Address of matrix[0] (heap): " << &matrix[0] << std::endl;
    return matrix;
}

int main() {
    auto matrix = generate_matrix(3, 4);
    std::cout << "Address of returned matrix (stack): " << &matrix << std::endl;
    std::cout << "Address of matrix[0] (heap): " << &matrix[0] << std::endl;
    return 0;
}
