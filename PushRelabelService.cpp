#include "PushRelabelService.h"

PushRelabelService::PushRelabelService()
{

}

PushRelabelService::~PushRelabelService()
{

}

int PushRelabelService::calculateMaxFlow(Graph* graph, int source, int destination)
{
	Graph* residualGraph = graph->clone();
	vector<int> queue;
	int* e = new int[graph->getNumberOfVertices()] ();
	int* h = new int[graph->getNumberOfVertices()] ();
	bool* inQueue = new bool[graph->getNumberOfVertices()] ();

	h[source] = graph->getNumberOfVertices();

	for (int i = 0; i < graph->getNumberOfVertices(); i++)
	{
		if (graph->getAdjacencyMatrix()[source][i] == 0)
		{
			continue;
		}
		residualGraph->getAdjacencyMatrix()[source][i] = 0;
		residualGraph->getAdjacencyMatrix()[i][source] = graph->getAdjacencyMatrix()[source][i];
		e[i] = graph->getAdjacencyMatrix()[source][i];
		if (i != destination)
		{
			queue.push_back(i);
			inQueue[i] = true;
		}
	}

	while (!queue.empty())
	{
		int u = queue[0];
		queue.erase(queue.begin());
		inQueue[u] = false;
		relabel(u, h, residualGraph);
		push(u, e, h, queue, inQueue, residualGraph, source, destination);
	}

	int result = e[destination];

	delete[] inQueue;
	delete[] h;
	delete[] e;
	delete residualGraph;
	
	return result;
}

void PushRelabelService::relabel(int u, int* h, Graph* residualGraph)
{
	int minHeight = INT_MAX;
	for (int i = 0; i < residualGraph->getNumberOfVertices(); i++)
	{
		if (residualGraph->getAdjacencyMatrix()[u][i] == 0)
		{
			continue;
		}
		if (residualGraph->getAdjacencyMatrix()[u][i] > 0)
		{
			minHeight = (h[i] < minHeight ? h[i] : minHeight);
		}
		h[u] = minHeight + 1;
	}
}

void PushRelabelService::push(int u, int* e, int* h, vector<int>& queue, bool* inQueue, Graph* residualGraph, int source, int destination)
{
	for (int i = 0; i < residualGraph->getNumberOfVertices(); i++)
	{
		if (residualGraph->getAdjacencyMatrix()[u][i] == 0)
		{
			continue;
		}
		if (e[u] == 0)
			break;
		if (residualGraph->getAdjacencyMatrix()[u][i] > 0 && h[i] < h[u])
		{
			int f = (e[u] < residualGraph->getAdjacencyMatrix()[u][i] ? e[u] : residualGraph->getAdjacencyMatrix()[u][i]);
			residualGraph->getAdjacencyMatrix()[u][i] -= f;
			residualGraph->getAdjacencyMatrix()[i][u] += f;
			e[u] -= f;
			e[i] += f;
			if (!inQueue[i] && i != source && i != destination)
			{
				queue.push_back(i);
				inQueue[i] = true;
			}
		}
	}
	if (e[u] != 0)
	{
		queue.push_back(u);
		inQueue[u] = true;
	}
}
