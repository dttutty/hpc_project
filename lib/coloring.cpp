
#include <array>
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>
#include <cmath>
#include "coloring.h"

const float EPS = 0.00001f;
const float SHRINKING_FACTOR = 7.5f;

// coloring a matrix using Fratarcangeli algorithm
std::array<std::vector<int>, 2> fratarcangeli(const std::vector<std::vector<float>>& A) {
    int n = A.size();
    std::vector<int> colors(n, -1);
    std::vector<int> degrees(n, 0);
    std::vector<int> order(n);
    std::iota(order.begin(), order.end(), 0);

    // Calculate the degree of each vertex
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            degrees[i] += A[i][j] != 0;
        }
    }

    // Sort vertices by degree in descending order
    std::sort(order.begin(), order.end(), [&](int a, int b) {
        return degrees[a] > degrees[b];
    });

    // Initialize the color of the first vertex to 0
    colors[order[0]] = 0;

    // Greedily color the remaining vertices
    for (int orderIndex = 1; orderIndex < n; orderIndex++) { 
        int vertex = order[orderIndex]; 

        // create a boolean array to mark used colors
        std::vector<bool> used(n, false); 

        // mark the colors of adjacent vertices as used
        for (int j = 0; j < n; j++) {
            if (A[vertex][j] != 0) {
                used[colors[j]] = true; 
            }
        }

        // find the first unused color
        for (int j = 0; j < n; j++) {
            if (!used[j]) {
                colors[vertex] = j;
                break;
            }
        }
    }

    // Find the number of colors used
    int num_colors = *std::max_element(colors.begin(), colors.end()) + 1;

    return {colors, order};
}


// std::array<std::vector<int>, 2> randomized_coloring(const std::vector<std::vector<float>>& A) {
//     int n = A.size();

//     std::set<int> neighbours[n];
//     std::vector<int> node_colors(n, -1);
//     std::vector<int> next_color(n, -1);
//     std::vector<std::set<int>> node_palettes(n);
//     std::set<int> U;

//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             if (i != j && fabs(A[i][j]) > EPS) {
//                 // add j to the neighbours of i if there is an edge between i and j
//                 if (neighbours[i].find(j) == neighbours[i].end()) {
// 					neighbours[i].insert(j);
// 				}
//                 // add i to the neighbours of j if there is an edge between i and j
// 				if (neighbours[j].find(i) == neighbours[j].end()) {
// 					neighbours[j].insert(i);
// 				}
//             }
//         }
//     }

//     // find the maximum degree of the graph
//     int max_degree = 0;
//     for (int i = 0; i < n; i++) {
//         max_degree = std::max(max_degree, (int)neighbours[i].size());
//     }

//     int max_color = int((float)max_degree / SHRINKING_FACTOR);
//     if (max_color <= 0) {
//         max_color = 1;
//     }
//     // max_color = 2;

//     for (int iv = 0; iv< n;++iv){
//         for (int ic = 0; ic < max_color; ++ic){
//             node_palettes[iv].insert(ic);
//         }
//         next_color[iv] = max_color;
//     }

    



// }
