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

	int graph_size = 4;
	int** matrix = new int*[graph_size];
	for (int i = 0; i < graph_size; i++)
	{
		matrix[i] = new int[graph_size];
	}
	for (int i = 0; i < graph_size; i++)
	{
		for (int j = 0; j < graph_size; j++)
		{
			matrix[i][j] = i == j ? 0 : j + 1;
		}
	}
	auto graph = new Graph(1, graph_size, matrix);
	graphs[graph->getId()] = graph;

	graph_size = 6;
	int** static_matrix = new int* [graph_size];
	for (int i = 0; i < graph_size; i++)
	{
		static_matrix[i] = new int[graph_size] ();
	}
	static_matrix[0][1] = 16;
	static_matrix[0][2] = 13;
	static_matrix[1][2] = 10;
	static_matrix[2][1] = 4;
	static_matrix[1][3] = 12;
	static_matrix[3][2] = 9;
	static_matrix[2][4] = 14;
	static_matrix[4][5] = 4;
	static_matrix[4][3] = 7;
	static_matrix[3][5] = 20;
	auto graph2 = new Graph(0, graph_size, static_matrix);
	graphs[graph2->getId()] = graph2;
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