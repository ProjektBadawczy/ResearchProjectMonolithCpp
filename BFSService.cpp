#include "BFSService.h"
#include <queue>

BFSService::BFSService()
{

}

BFSService::~BFSService()
{

}

BFSResult* BFSService::bfs(Graph* graph, int source, int t)
{
	int numberOfVertices = graph->getNumberOfVertices();
	int* parent = new int[numberOfVertices];
	bool* visited = new bool[numberOfVertices];
	auto adjacencyMatrix = graph->getAdjacencyMatrix();
	for (int i = 0; i < numberOfVertices; i++)
	{
		visited[i] = false;
	}
	auto q = new std::queue<int>();
	q->push(source);
	visited[source] = true;
	parent[source] = -1;
	while (q->size() != 0)
	{
		int u = q->front();
		q->pop();
		for (int v = 0; v < numberOfVertices; v++)
		{
			if (!visited[v] && adjacencyMatrix[u][v] > 0)
			{
				q->push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}
	delete q;
	bool success = visited[t];
	delete[] visited;
	return new BFSResult(parent, success);
}