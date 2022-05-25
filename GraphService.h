#pragma once
#include "GraphRepository.h"
class GraphService
{
public:
	GraphService(GraphRepository* graphRepository);
	~GraphService();
	Graph* getGraph(int id);
private:
	GraphRepository* graphRepository;
};