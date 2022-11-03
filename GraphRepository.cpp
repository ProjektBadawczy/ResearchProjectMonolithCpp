#include "GraphRepository.h"

GraphRepository::GraphRepository(string filepath)
{
	readGraphsFromJson(filepath);
}

GraphRepository::~GraphRepository()
{
	for (auto graph : graphs)
	{
		delete graph;
	}
	graphs.clear();
	for (auto directedGraph : directedGraphs)
	{
		delete directedGraph;
	}
	directedGraphs.clear();
}

Graph* GraphRepository::getGraph(int id)
{
	return (id > 0 && id <= graphs.size()) ? graphs[id - 1]->clone() : nullptr;
}

DirectedGraph* GraphRepository::getDirectedGraph(int id)
{
	return (id > 0 && id <= directedGraphs.size()) ? directedGraphs[id - 1]->clone() : nullptr;
}

void GraphRepository::readGraphsFromJson(string path)
{
	ifstream t(path);
	stringstream buffer;
	buffer << t.rdbuf();
	string graphName = "\"graph\": ";
	string directedGraphName = "\"directedGraph\": ";
	size_t pos = 0;
	size_t nextStopPos = 0;
	Graph* graph;
	DirectedGraph* directedGraph;

	// read graphs from json
	// graphs should be formatted as [{graph, directedGraph}, {graph, directedGraph}, ...]
	while (true)
	{
		pos = buffer.str().find(graphName, pos);
		if (pos == string::npos) break;
		// graphs always end with "},"
		nextStopPos = buffer.str().find("},", pos);
		graph = new Graph(utility::conversions::to_string_t(buffer.str().substr(pos, nextStopPos - pos + 1)));
		graphs.push_back(graph);
		pos = buffer.str().find(directedGraphName, nextStopPos);
		if (pos == string::npos) break;
		// directed graphs always end with "}}"
		nextStopPos = buffer.str().find("}}", pos);
		directedGraph = new DirectedGraph(utility::conversions::to_string_t(buffer.str().substr(pos, nextStopPos - pos + 1)));
		directedGraphs.push_back(directedGraph);
	}
}
