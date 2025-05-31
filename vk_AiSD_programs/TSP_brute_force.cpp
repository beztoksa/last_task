#include <vector>
#include <climits>
#include <algorithm>
#include "TSP_brute_force.h"
double TSP_brute_force(MatrixGraph& Matrix) {
    int n = Matrix.VerticesCount();
    std::vector<int> vertices(n);
    for (int i = 0; i < n; ++i) vertices[i] = i;
    double minSum = INT_MAX;

    while (true) {
        double currentSum = 0;

        for (int i = 0; i < n - 1; ++i) {
            int from = vertices[i];
            int to = vertices[i + 1];
            currentSum += Matrix.GetWeight(from,to);
        }
        currentSum += Matrix.GetWeight(vertices[n-1], vertices[0]);
        minSum = std::min(minSum, currentSum);

        if (!std::next_permutation(vertices.begin() + 1, vertices.end()))
            break;
    }

    return minSum;
}