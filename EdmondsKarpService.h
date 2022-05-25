#pragma once
#include "BFSService.h"

class EdmondsKarpService
{
public:
	EdmondsKarpService(BFSService* bfsService);
	~EdmondsKarpService();
	int calculateMaxFlow(Graph* graph, int source, int destination);
private:
	BFSService* bfsService;
	bool areSourceAndGraphParametersValid(Graph* graph, int source, int destination);
};