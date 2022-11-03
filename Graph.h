#pragma once
#include <string>
#include <cpprest/http_msg.h>
using namespace utility;

class Graph
{
public:
	Graph(int id, int numberOfVertices, int** adjacencyMatrix);
	Graph(string_t text);
	~Graph();
	Graph* clone();
	int getId();
	int getNumberOfVertices();
	int** getAdjacencyMatrix();
	string_t toString();
private:
	int id;
	int numberOfVertices;
	int** adjacencyMatrix;
};