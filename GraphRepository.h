#pragma once
#include "Graph.h"
using namespace std;
class GraphRepository
{
public:
	GraphRepository();
	~GraphRepository();
	Graph* getGraph(int id);
private:
	Graph** graphs;
	int size;
};