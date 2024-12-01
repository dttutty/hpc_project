

#include "coloring.h"

typedef std::vector<int> Partition;
typedef const std::vector<std::vector<float>> Matrix;

std::vector<std::vector<int>> greedy_coloring(const Matrix& A) {
    int V = A.size(); // number of vertices
    std::vector<int> result(V, -1); // color of each vertex, -1 means not colored yet
    std::vector<std::vector<int>> color_groups; // groups of vertices by color

    // Assign the first color to the first vertex
    result[0] = 0;

    // A temporary array to store the available colors
    std::vector<bool> available(V, false);

    // Assign colors to remaining vertices
    for (int u = 1; u < V; u++) {
        // Process all adjacent vertices and flag their colors as unavailable
        for (int v = 0; v < V; v++) {
            if (A[u][v] != 0 && result[v] != -1) {
                available[result[v]] = true;
            }
        }

        // Find the first available color
        int cr;
        for (cr = 0; cr < V; cr++) {
            if (!available[cr]) {
                break;
            }
        }

        // Assign the found color to the vertex
        result[u] = cr;

        // Reset the available array for the next vertex
        for (int v = 0; v < V; v++) {
            if (A[u][v] != 0 && result[v] != -1) {
                available[result[v]] = false;
            }
        }
    }

    // Group vertices by color
    for (int u = 0; u < V; u++) {
        int color = result[u];
        if (color >= color_groups.size()) {
            color_groups.resize(color + 1);
        }
        color_groups[color].push_back(u);
    }

    return color_groups;
}
