#pragma once
#include "BFSResult.h"
#include "Graph.h"
class BFSService
{
public:
	BFSService();
	~BFSService();
	BFSResult* bfs(Graph* graph, int source, int t);
};