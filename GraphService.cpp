#include"GraphService.h"

GraphService::GraphService(GraphRepository* graphRepository)
{
	this->graphRepository = graphRepository;
}

GraphService::~GraphService()
{
	delete graphRepository;
}

Graph* GraphService::getGraph(int id)
{
	return graphRepository->getGraph(id);
}

DirectedGraph* GraphService::getDirectedGraph(int id)
{
	return graphRepository->getDirectedGraph(id);
}