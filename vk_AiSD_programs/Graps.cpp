#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <climits>
#include <set>
#include <stack>
#include <algorithm>
#include "Graps.h"
std::vector<int> pre_order(ListGraph& Graph)
{
    std::stack<int> stack;
    std::vector<bool> visited(Graph.VerticesCount(), false);
    std::vector<int> way;
    stack.push(0);
    while (!stack.empty())
    {
        int v = stack.top();
        stack.pop();
        if (!visited[v])
        {
            visited[v] = true;
            way.push_back(v);
			const std::vector<int>& child = Graph.GetNextVertices(v);
			for (int i = child.size() - 1; i >= 0; i--)
            {
                if (!visited[child[i]])
                {
                    stack.push(child[i]);
                }
            }
        }
    }
    return way;

}
ArcGraph::ArcGraph(int size)
	: verticescount(size)
{
}



void ArcGraph::AddEdge(int from, int to, double weight)
{
	assert(0 <= from && from < verticescount);
	assert(0 <= to && to < verticescount);
	adjacencyLists.push_back({ weight, from,to });
}

int ArcGraph::VerticesCount() const
{
	return verticescount;
}
std::vector <std::tuple<double, int, int>>& ArcGraph::GetSortedEdges()
{
	std::sort(adjacencyLists.begin(), adjacencyLists.end());
	return adjacencyLists;
}


MatrixGraph::MatrixGraph(int size)
	: adjacencyLists(size, std::vector<double>(size, 0))
{
}


void MatrixGraph::AddEdgeTwice(int from, int to, double weight)
{
	assert(0 <= from && from < adjacencyLists.size());
	assert(0 <= to && to < adjacencyLists.size());
	adjacencyLists[from][to] = weight;
	adjacencyLists[to][from] = weight;
}

int MatrixGraph::VerticesCount() const
{
	return (int)adjacencyLists.size();
}
double MatrixGraph::GetWeight(int from,int to) const
{
	return adjacencyLists[from][to];
}

DSU::DSU(size_t size)
	: parent(size), rank(size, 1)
{
	for (int i = 0; i < size; i++)
	{
		parent[i] = i;
	}
}

size_t DSU::find_set(size_t u)
{
	std::stack<size_t> stack;
	stack.push(u);

	while (parent[u] != u)
	{
		stack.push(parent[u]);
		u = parent[u];
	}

	size_t& root = u;

	while (!stack.empty())
	{
		parent[stack.top()] = root;
		stack.pop();
	}

	return root;
}

bool DSU::union_set(size_t u, size_t v)
{
	u = find_set(u);
	v = find_set(v);

	if (u != v)
	{
		if (rank[u] < rank[v])
			std::swap(u, v);

		parent[v] = u;
		rank[u] += rank[v];
		return true;
	}
	return false;

}
ListGraph::ListGraph(int size)
	: adjacencyLists(size)
{
}



void ListGraph::AddEdgeTwice(int from, int to)
{
	assert(0 <= from && from < adjacencyLists.size());
	assert(0 <= to && to < adjacencyLists.size());
	adjacencyLists[from].push_back(to);
	adjacencyLists[to].push_back(from);
}

int ListGraph::VerticesCount() const
{
	return (int)adjacencyLists.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const
{
	assert(0 <= vertex && vertex < adjacencyLists.size());
	return adjacencyLists[vertex];
}

