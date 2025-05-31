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
    void AddEdge(int from, int to, int weight)
    {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from].push_back({ weight,to });
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


private:
    std::vector<std::vector<std::pair<int, int>>> adjacencyLists;
    // первое число вес, второе номер вершины
};
void DecreaseKey(std::set<std::pair<int, int>>& q, int v, int old_d, int new_d)
{
    if (q.find({ old_d,v }) != q.end())
    {
        q.erase(q.find({ old_d, v }));
        q.insert({ new_d,v });
    }
}
int Prima(const ListGraph& graph, int start_vertex)
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

            if (d[v] == INT_MAX)
            {
                d[v] = v_weight;
                pi[v] = u;
                q.insert({ d[v],v });
            }
            else if (q.find({ d[v],v }) != q.end() && d[v] > v_weight)
            {
                int old_d = d[v];
                d[v] = v_weight;
                pi[v] = u;
                DecreaseKey(q, v, old_d, d[v]);
            }

        }
    }
    int sum = 0;
    for (int weight : d)
    {
        sum += weight;
    }
    return sum;

}
