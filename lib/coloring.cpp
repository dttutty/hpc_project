
#include "coloring.h"

const float EPS = 0.00001f;
const float SHRINKING_FACTOR = 7.5f;
const int NO_PROGRESS_STREAK_THRESHOLD = 100;

typedef std::vector<int> Partition;
typedef const std::vector<std::vector<float>> Matrix;


// std::vector<Partition> randomized_graph_coloring(const Matrix& A) {
//     int N = A.size();
// 	std::set<int> neighbours[N];

// 	int node_colors[N]; // colors assigned to the nodes.
// 	int next_color[N]; // next color of every node, in case the palette runs out.				 
// 	std::set<int> node_palettes[N]; // palettes of the nodes.
// 	std::set<int> U;

// 	/*
// 	Every node needs to know about it's neighbours. so find that.
// 	There is an edge between two nodes i and j, if the matrix coefficient at row i, column j is non-zero.
// 	*/
//     std::cout << "needs to know" << std::endl;

//     // #pragma omp parallel for
// 	for (int i = 0; i < N; ++i) {
// 		for (int j = 0; j < N; ++j) {
// 			if (i != j && fabs(A[i][j]) > EPS) {

// 				// if necessary, make j a neighbour of i.
// 				if (neighbours[i].find(j) == neighbours[i].end()) {
// 					neighbours[i].insert(j);
// 				}

// 				// if necessary, make i a neighbour of j.
// 				if (neighbours[j].find(i) == neighbours[j].end()) {
// 					neighbours[j].insert(i);
// 				}
// 			}
// 		}
// 	}

// 	// calculate max degree of a single node.
//     std::cout << "calculate max degree" << std::endl;
// 	int delta_v = 0;
// 	for (int i = 0; i < N; ++i) {
// 		if ((int)neighbours[i].size() > delta_v) {
// 			delta_v = neighbours[i].size();
// 		}
// 	}

// 	// initially, every node has a palette of size delta_v/shrinking_factor.
// 	// the maximum number of colors necessary for a graph coloring is delta_v, but many
// 	// graphs won't need that many colors. therefore, we choose to shrink delta_v by a shrinking factor.
// 	// if the shrinking factor is too big, so that the problem is unsolvable, then more colors will be added on the fly.
// 	int max_color = int((float)delta_v / SHRINKING_FACTOR);
// 	if (max_color <= 0) {
// 		max_color = 1;
// 	}
// 	max_color = 2;

// 	// initialize the palettes for all the node.
// 	// the colors in the palette will be chosen randomly from, for all the remaining nodes in U.
//     std::cout << "initialize the palettes" << std::endl;
// 	for (int iv = 0; iv < N; ++iv) {
// 		for (int ic = 0; ic < max_color; ++ic) {
// 			node_palettes[iv].insert(ic);
// 		}
// 		next_color[iv] = max_color;
// 	}

// 	for (int iv = 0; iv < N; ++iv) {
// 		U.insert(iv);
// 	}

// 	// keep track of the number of iterations with no progress.
// 	int no_progress_streak = 0;

// 	/*
// 	If a node has found a color that solves the graph coloring for that node, then remove from U.
// 	Once U is empty, the graph coloring problem is done.
// 	*/
//     std::cout << "remove from U" << std::endl;
//     std::vector<int> vec(U.begin(), U.end());
// 	while (U.size()) {

// 		// all remaining nodes in U are given a random color.
//         std::cout << "1" << std::endl;
//         #pragma omp parallel for
// 		for (int i = 0; i < vec.size(); i++) {
//             int iv = vec[i];
// 			// get random color from palette, and assign it.
// 			int m = rand() % node_palettes[iv].size();
// 			auto setIt = node_palettes[iv].begin();
// 			advance(setIt, m);

// 			node_colors[iv] = *setIt;
// 		}

// 		std::set<int> temp;


// 		/*
// 		  Now let's find all the nodes whose colors are different from all their neighbours.
// 		  Those nodes will be removed from U, because they are done, with respect to the graph coloring problem.
// 		*/
//         std::cout << "2" << std::endl;
// 		for (int i = 0; i < vec.size(); i++) {
//             int iv = vec[i];
// 			int icolor = node_colors[iv];

// 			/*
// 			Check if graph coloring property is solved for node.
// 			*/
// 			bool different_from_neighbours = true;
// 			for (int neighbour : neighbours[iv]) {

// 				if (node_colors[neighbour] == icolor) {
// 					different_from_neighbours = false;
// 					break;
// 				}
// 			}

// 			if (different_from_neighbours) {
// 				// found the right color for this one.
// 				// so remove from U.

// 				// also, the neighbours of iv can't use this color anymore.
// 				// so remove it from their palettes.
// 				for (int neighbour : neighbours[iv]) {
// 					node_palettes[neighbour].erase(icolor);
// 				}

// 			}
// 			else {
// 				// not a correct color. don't remove from U.
// 				temp.insert(iv);
// 			}

// 			// feed the hungry!
// 			// if palette empty, we add more colors on the fly.
// 			// if we don't do this, the algorithm will get stuck in a loop.
// 			if (node_palettes[iv].empty()) {
// 				node_palettes[iv].insert(next_color[iv]++);
// 			}

// 		}

//         std::cout << "3" << std::endl;
// 		if (U.size() == temp.size()) {
// 			no_progress_streak++;

// 			// if no progress for too many iterations, we have no choice but to feed a random node.
// 			if (no_progress_streak > NO_PROGRESS_STREAK_THRESHOLD) {
// 				int m = rand() % U.size();
// 				auto setIt = U.begin();
// 				advance(setIt, m);

// 				node_palettes[*setIt].insert(next_color[*setIt]++);

// 				no_progress_streak = 0;
// 			}
// 		}

// 		U = temp;
// 	}

// 	// find the number of colors used in our solution.
// 	// this is also the number of partitions.

//     std::cout << "find the number of colors" << std::endl;
// 	int num_colors = 0;
// 	for (int i = 0; i < N; ++i) {
// 		if (next_color[i] > num_colors) {
// 			num_colors = next_color[i];
// 		}
// 	}

// 	/*
// 	Finally, we collect all the partitions then.
// 	*/
//     std::cout << "collect all the partitions" << std::endl;
// 	std::vector<Partition> partitions;
// 	for (int ic = 0; ic < num_colors; ++ic) {
// 		Partition partition;

// 		/*
// 		The first partition is all nodes that use color 0,
// 		the second partition use color 1, and so on.
// 		*/
// 		for (int inode = 0; inode < N; ++inode) {
// 			if (node_colors[inode] == ic) {
// 				partition.push_back(inode);
// 			}
// 		}

// 		partitions.push_back(partition);
// 	}

// 	return partitions;
// }


std::vector<std::vector<int>> greedy_coloring(const Matrix& A) {
    int N = A.size();
    std::vector<int> coloring(N, -1);  // 每个节点的颜色，初始为-1，表示未着色
    std::vector<std::vector<int>> result;  // 存储每个颜色的节点

    // 按照节点的度数进行排序，度数大的节点优先着色
    std::vector<int> order(N);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&](int a, int b) {
        return A[a].size() > A[b].size();
        });

    // OpenMP 并行化节点着色的过程
#pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        int node = order[i];
        std::vector<bool> available(N, false);  // 用来标记已经被邻居占用的颜色

        // 遍历邻居并标记已使用的颜色
        for (int neighbor : A[node]) {
            if (coloring[neighbor] != -1) {  // 如果邻居已经着色
                available[coloring[neighbor]] = true;
            }
        }

        // 找到第一个可用的颜色
        int color;
        for (color = 0; color < N; ++color) {
            if (!available[color]) break;
        }

        // 给节点着色
        coloring[node] = color;

        // 将已着色的节点放入结果中（通过临界区保护访问）
#pragma omp critical
        {
            if (result.size() <= color) {
                result.resize(color + 1);  // 确保颜色的数量足够
            }
            result[color].push_back(node);
        }
    }

    return result;
}
