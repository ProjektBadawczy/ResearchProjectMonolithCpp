#include "PushRelabelService.h"

PushRelabelService::PushRelabelService()
{

}

PushRelabelService::~PushRelabelService()
{

}

int PushRelabelService::calculateMaxFlow(DirectedGraph* graph, int source, int destination)
{
	auto residualGraph = initResidualGraph(graph);
	std::queue<int>* queue = new std::queue<int>;
	int* e = new int[graph->getNumberOfVertices()]();
	int* h = new int[graph->getNumberOfVertices()]();
	bool* inQueue = new bool[graph->getNumberOfVertices()]();
	h[source] = graph->getNumberOfVertices();
	for (auto v : graph->getAdjacencyList()[source])
	{
		residualGraph->getNeighbour(source, v->i)->w = 0;
		residualGraph->getNeighbour(v->i, source)->w = v->w;
		e[v->i] = v->w;
		if (v->i != destination)
		{
			queue->push(v->i);
			inQueue[v->i] = true;
		}
	}
	while (!queue->empty())
	{
		int u = queue->front();
		queue->pop();
		inQueue[u] = false;
		relabel(u, h, residualGraph);
		push(u, e, h, queue, inQueue, residualGraph, source, destination);
	}
	int ret = e[destination];
	delete[] inQueue;
	delete[] h;
	delete[] e;
	delete queue;
	delete residualGraph;
	return ret;
}

DirectedGraph* PushRelabelService::initResidualGraph(DirectedGraph* graph)
{
	auto residualGraph = new DirectedGraph(graph->getNumberOfVertices(), graph->getId());
	for (int u = 0; u < graph->getNumberOfVertices(); u++)
	{
		for (DirectedGraph::Vertex* v : graph->getAdjacencyList()[u])
		{
			// If edge exists in residual graph
			// update its weight
			if (residualGraph->hasEdge(u, v->i))
			{
				residualGraph->getNeighbour(u, v->i)->w += v->w;
			}
			// else add the edge
			else
			{
				residualGraph->addEdge(u, v->i, v->w);
			}
			// If there is no backward edge,
			// create one with 0 weight
			if (!residualGraph->hasEdge(v->i, u))
			{
				residualGraph->addEdge(v->i, u, 0);
			}
		}
	}
	return residualGraph;
}

void PushRelabelService::relabel(int u, int* h, DirectedGraph* residualGraph)
{
	int minHeight = INT_MAX;
	for (auto v : residualGraph->getAdjacencyList()[u])
	{
		if (v->w > 0)
		{
			minHeight = std::min(h[v->i], minHeight);
		}
	}
	h[u] = minHeight + 1;
}

void PushRelabelService::push(int u, int* e, int* h, std::queue<int>* queue,
	bool* inQueue, DirectedGraph* residualGraph, int source, int destination)
{
	for (auto v : residualGraph->getAdjacencyList()[u])
	{
		if (e[u] == 0)
		{
			break;
		}

		if (v->w > 0 && h[v->i] < h[u])
		{
			int f = std::min(e[u], v->w);
			v->w -= f;
			residualGraph->getNeighbour(v->i, u)->w += f;
			e[u] -= f;
			e[v->i] += f;

			if (!inQueue[v->i] && v->i != source && v->i != destination)
			{
				queue->push(v->i);
				inQueue[v->i] = true;
			}
		}
	}

	// If after flow to all neighbours the
	// excess in current vertex is still
	// above 0, add it to queue again
	if (e[u] != 0)
	{
		queue->push(u);
		inQueue[u] = true;
	}
}
