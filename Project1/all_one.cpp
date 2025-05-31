#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <climits>
#include <set>

struct ListGraph
{
public:
    ListGraph(int size)
        : adjacencyLists(size)
    {
    }
    ~ListGraph()
    {
    }

    void AddEdgeTwice(int from, int to, int weight)
    {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from].push_back({ weight,to });
        adjacencyLists[to].push_back({ weight,from });

    }

    int VerticesCount() const
    {
        return (int)adjacencyLists.size();
    }

    std::vector<std::pair<int, int>> GetNextVertices(int vertex) const
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        return adjacencyLists[vertex];
    }
    int GetWeight(int from, int to) const
    {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        int minweight = INT_MAX;
        for (const auto& [weight, vertex] : adjacencyLists[from])
        {
            if (vertex == to && weight < minweight)
            {
                minweight = weight;
            }
        }
        return minweight;
    }


private:
    std::vector<std::vector<std::pair<int, int>>> adjacencyLists;
    // первое число вес, второе номер вершины
};
bool Relax(const ListGraph& graph, std::vector<int>& d, std::vector<int>& pi, int u, int v)
{
    int weight = graph.GetWeight(u, v);
    if (d[v] > d[u] + weight)
    {
        d[v] = d[u] + weight;
        pi[v] = u;
        return true;
    }
    return false;

}
void DecreaseKey(std::set<std::pair<int, int>>& q, int v, int old_d, int new_d)
{
    q.erase(q.find({ old_d, v }));
    q.insert({ new_d,v });
}
int Dijkstra(const ListGraph& graph, int start_vertex, int end_vertex)
{
    int size = graph.VerticesCount();
    std::vector<int> pi(size, -1);
    std::vector<int>d(size, INT_MAX);
    d[start_vertex] = 0;
    std::set<std::pair<int, int>> q;
    q.insert({ 0,start_vertex });
    while (!q.empty())
    {
        auto [u_weight, u] = *q.begin();
        q.erase(q.begin());
        for (const auto& [v_weight, v] : graph.GetNextVertices(u))
        {
            int old_d = d[v];
            if (d[v] == INT_MAX)
            {
                d[v] = d[u] + graph.GetWeight(u, v);
                pi[v] = u;
                q.insert({ d[v],v });
            }
            else if (Relax(graph, d, pi, u, v))
            {
                DecreaseKey(q, v, old_d, d[v]);
            }
        }
    }
    return d[end_vertex];

}
int main(int argc, const char* argv[]) {
    int N = 0;
    std::cin >> N;
    ListGraph Graph(N);
    int M = 0;
    std::cin >> M;
    int u = 0, v = 0, w = 0;
    for (int i = 0; i < M; i++)
    {
        std::cin >> u >> v >> w;
        Graph.AddEdgeTwice(u, v, w);

    }
    int s = 0, t = 0;
    std::cin >> s >> t;
    std::cout << Dijkstra(Graph, s, t);

    return 0;
}
