#include "coloring.h"

typedef const std::vector<std::vector<float>> Matrix;

std::vector<std::vector<int>> greedy_coloring(const Matrix& A) {
    int n = A.size(); // number of vertices
    std::vector<int> result(n, -1); // color of each vertex, -1 means not colored yet
    std::vector<std::vector<int>> color_groups; // groups of vertices by color

    // Assign the first color to the first vertex
    result[0] = 0;

    // A temporary array to store the availability of colors
    std::vector<bool> color_used(n, false);

    // Assign colors to remaining vertices
    for (int u = 1; u < n; u++) {
        // Process all adjacent vertices and flag their colors as unavailable
        for (int v = 0; v < n; v++) {
            if (A[u][v] != 0 && result[v] != -1) {
                auto color_of_v = result[v];
                color_used[color_of_v] = true;
            }
        }

        // Find the first available color
        int color_id;
        for (color_id = 0; color_id < n; color_id++) {
            if (color_used[color_id] == false) {
                break;// found an available color for current node: color_id
            }
        }

        // Assign the found color to the vertex and reset the color_used array
        result[u] = color_id;
        std::fill(color_used.begin(), color_used.end(), false);
    }

    // Group vertices by color
    for (int u = 0; u < n; u++) {
        int color = result[u];
        if (color >= color_groups.size()) {
            color_groups.resize(color + 1);
        }
        color_groups[color].push_back(u);
    }

    return color_groups;
}
