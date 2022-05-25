#include "Graph.h"

using namespace std;

Graph::Graph(int id, int numberOfVertices, int** adjacencyMatrix)
{
	this->id = id;
	this->numberOfVertices = numberOfVertices;
	this->adjacencyMatrix = adjacencyMatrix;
}

Graph::~Graph()
{
	for (int i = 0; i < this->numberOfVertices; i++)
	{
		delete[] this->adjacencyMatrix[i];
	}
	delete[] this->adjacencyMatrix;
}

Graph* Graph::clone()
{
	int** matrix = new int* [numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++)
	{
		matrix[i] = new int[numberOfVertices];
	}
	for (int i = 0; i < numberOfVertices; i++)
	{
		for (int j = 0; j < numberOfVertices; j++)
		{
			matrix[i][j] = adjacencyMatrix[i][j];
		}
	}
	return new Graph(id, numberOfVertices, matrix);
}

int Graph::getId()
{
	return id;
}

int Graph::getNumberOfVertices()
{
	return numberOfVertices;
}

int** Graph::getAdjacencyMatrix()
{
	return adjacencyMatrix;
}

string Graph::toString()
{
	string result = "";
	result += "{";
	result += "id: ";
	result += to_string(id);
	result += ",";
	result += "numerOfVertices: ";
	result += to_string(numberOfVertices);
	result += ",";
	result += "adjacencyMatrix: [";
	for (int i = 0; i < numberOfVertices; i++)
	{
		result += "[";
		for (int j = 0; j < numberOfVertices; j++)
		{
			result += to_string(adjacencyMatrix[i][j]);
			if (j != numberOfVertices - 1)
			{
				result += ",";
			}
		}
		result += "]";
		if (i != numberOfVertices - 1)
		{
			result += ",";
		}
	}
	result += "]";
	return result;
}