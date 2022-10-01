#pragma once
#include <queue>
#include "Graph.h"
using namespace std;
class PushRelabelService
{
public:
	PushRelabelService();
	~PushRelabelService();
	int calculateMaxFlow(Graph* graph, int source, int destination);
private:
	void relabel(int u, int* h, Graph* residualGraph);
	void push(int u, int* e, int* h, queue<int>* queueGiven, bool* inQueue, Graph* residualGraph, int source, int destination);
};