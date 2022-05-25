#include "GraphRepository.h"

GraphRepository::GraphRepository()
{
	// set initial size of array to 100
	// expand when necessary
	size = 100;
	graphs = new Graph* [size];
	for (int i = 0; i < size; i++)
	{
		graphs[i] = nullptr;
	}
	int** matrix = new int*[4];
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
	delete[] graphs;
}

Graph* GraphRepository::getGraph(int id)
{
	return graphs[id]->clone();
}