#include "TSP_approximate.h"
double TSP_approximate(ArcGraph& Graph, MatrixGraph& Matrix)
{
    auto Edges = Graph.GetSortedEdges();
    DSU dsu (Graph.VerticesCount());
    double sum = 0;
    ListGraph listGraph(Graph.VerticesCount());
    for (const auto& [weight, from, to] : Edges)
    {
        if (dsu.union_set(from, to))
        {
            listGraph.AddEdgeTwice(from, to);
        }
    }
    std::vector<int> way = pre_order(listGraph);
    for (size_t i = 0; i < way.size(); i++)
    {
        //std::cout << way[i]<<' ';
            int cur = way[i];
            int next = way[(i + 1) % way.size()];
            double weight = Matrix.GetWeight(cur, next);
                sum += weight;
    }
    //std::cout << std::endl;
    return sum;
}
