#pragma once
#include "GraphRepository.h"
class GraphService
{
public:
	GraphService(GraphRepository* graphRepository);
	~GraphService();
	Graph* getGraph(int id);
	DirectedGraph* getDirectedGraph(int id);
private:
	GraphRepository* graphRepository;
};