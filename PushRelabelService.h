#pragma once
#include "DirectedGraph.h"
#include <queue>

class PushRelabelService
{
public:
	PushRelabelService();
	~PushRelabelService();
	int calculateMaxFlow(DirectedGraph* graph, int source, int destination);
private:
	DirectedGraph* initResidualGraph(DirectedGraph* graph);
	void relabel(int u, int* h, DirectedGraph* residualGraph);
	void push(int u, int* e, int* h, std::queue<int>* queue, bool* inQueue, DirectedGraph* residualGraph, int source, int destination);
};
