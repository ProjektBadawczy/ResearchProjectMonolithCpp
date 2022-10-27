#include "GraphRepository.h"

GraphRepository::GraphRepository()
{
	// set initial size of array to 100
	// expand when necessary
	size = 100;
	graphs = new Graph * [size]();
	directedGraphs = new DirectedGraph * [size]();
	initRepository();
}

GraphRepository::~GraphRepository()
{
	for (int i = 0; i < size; i++)
	{
		if (graphs[i] != nullptr)
		{
			delete graphs[i];
		}
	}
	for (int i = 0; i < size; i++)
	{
		if (directedGraphs[i] != nullptr)
		{
			delete directedGraphs[i];
		}
	}
	delete[] graphs;
	delete[] directedGraphs;
}

void GraphRepository::initRepository()
{
	int** matrix = new int* [4];
	for (int i = 0; i < 4; i++)
	{
		matrix[i] = new int[4];
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix[i][j] = i == j ? 0 : j + 1;
		}
	}
	auto graph = new Graph(1, 4, matrix);
	graphs[graph->getId()] = graph;

	auto directedGraph = new DirectedGraph(6, 1);
	directedGraph->addEdge(0, 1, 16);
	directedGraph->addEdge(0, 2, 13);
	directedGraph->addEdge(1, 2, 10);
	directedGraph->addEdge(2, 1, 4);
	directedGraph->addEdge(1, 3, 12);
	directedGraph->addEdge(3, 2, 9);
	directedGraph->addEdge(2, 4, 14);
	directedGraph->addEdge(4, 5, 4);
	directedGraph->addEdge(4, 3, 7);
	directedGraph->addEdge(3, 5, 20);
	directedGraphs[directedGraph->getId()] = directedGraph;
}

Graph* GraphRepository::getGraph(int id)
{
	return (id < 0 || id >= size || graphs[id] == nullptr) ? nullptr : graphs[id]->clone();
}

DirectedGraph* GraphRepository::getDirectedGraph(int id)
{
	return (id < 0 || id >= size || directedGraphs[id] == nullptr) ? nullptr : directedGraphs[id]->clone();
}