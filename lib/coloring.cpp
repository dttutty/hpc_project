#include "coloring.h"

typedef const std::vector<std::vector<float>> Matrix;

std::vector<std::vector<int>> greedy_coloring(const Matrix& A) {
    int n = A.size(); // number of vertices
    std::vector<int> result(n, -1); // color of each vertex, -1 means not colored yet
    std::vector<std::vector<int>> color_groups; // groups of vertices by color

    // Assign the first color to the first vertex
    result[0] = 0;

    // A temporary array to store the is_color_used_by_neighbors
    std::vector<bool> is_color_used_by_neighbors(n, false);

    // Assign colors to remaining vertices
    for (int u = 1; u < n; u++) {
        // Process all adjacent vertices and flag their colors as unavailable
        for (int v = 0; v < n; v++) {
            if (A[u][v] != 0 && result[v] != -1) {
                auto color_of_v = result[v];
                is_color_used_by_neighbors[color_of_v] = true;
            }
        }

        // Find the first is_color_used_by_neighbors
        int color_id;
        for (color_id = 0; color_id < n; color_id++) {
            if (!is_color_used_by_neighbors[color_id]) {
                break;
            }
        }

        // Assign the found color to the vertex
        result[u] = color_id;

        // Reset the is_color_used_by_neighbors array for the next vertex
        for (int v = 0; v < n; v++) {
            if (A[u][v] != 0 && result[v] != -1) {
                is_color_used_by_neighbors[result[v]] = false;
            }
        }
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
