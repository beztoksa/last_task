#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <climits>
#include <set>
#include <stack>
#include <algorithm>
struct ListGraph
{
public:
    ListGraph(int size);



    void AddEdgeTwice(int from, int to);

    int VerticesCount() const;

    std::vector<int> GetNextVertices(int vertex) const;


private:
    std::vector<std::vector<int>> adjacencyLists;
};
std::vector<int> pre_order(ListGraph& Graph);

struct ArcGraph
{
public:
    ArcGraph(int size);



    void AddEdge(int from, int to, double weight);
    int VerticesCount() const;
    std::vector <std::tuple<double, int, int>>& GetSortedEdges();


private:
    std::vector<std::tuple<double, int, int>> adjacencyLists;
    // weight, from, to.
    int verticescount;
};

struct MatrixGraph
{
public:
    MatrixGraph(int size);


    void AddEdgeTwice(int from, int to, double weight);

    int VerticesCount() const;
    double GetWeight(int from, int to) const;
private:
    std::vector<std::vector<double>> adjacencyLists;
};

class DSU
{
public:
    DSU(size_t size);
    size_t find_set(size_t u);

    bool union_set(size_t u, size_t v);

private:
    std::vector<size_t> parent;
    std::vector<size_t> rank;
};

