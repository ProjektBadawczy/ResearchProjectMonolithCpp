#pragma once
#include "Graph.h"
#include "DirectedGraph.h"
using namespace std;
class GraphRepository
{
public:
	GraphRepository();
	~GraphRepository();
	Graph* getGraph(int id);
	DirectedGraph* getDirectedGraph(int id);
private:
	void initRepository();
	Graph** graphs;
	DirectedGraph** directedGraphs;
	int size;
};