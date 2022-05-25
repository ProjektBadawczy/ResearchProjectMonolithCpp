#pragma once
#include<string>

class Graph
{
public:
	Graph(int id, int numberOfVertices, int** adjacencyMatrix);
	~Graph();
	Graph* clone();
	int getId();
	int getNumberOfVertices();
	int** getAdjacencyMatrix();
	std::string toString();
private:
	int id;
	int numberOfVertices;
	int** adjacencyMatrix;
};