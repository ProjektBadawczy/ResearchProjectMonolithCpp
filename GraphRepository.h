#pragma once
#include <vector>
#include <algorithm>
#include "Graph.h"
#include "DirectedGraph.h"
using namespace std;
class GraphRepository
{
public:
	GraphRepository(string filepath);
	~GraphRepository();
	Graph* getGraph(int id);
	DirectedGraph* getDirectedGraph(int id);
private:
	vector<Graph*> graphs;
	vector<DirectedGraph*> directedGraphs;
	void readGraphsFromJson(string path);
};