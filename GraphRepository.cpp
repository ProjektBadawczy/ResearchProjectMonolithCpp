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
	auto predicate = [=](Graph* graph)
	{
		return graph->getId() == id;
	};
	auto result = std::find_if(graphs.begin(), graphs.end(), predicate);
	return result != graphs.end() ? (*result)->clone() : nullptr;
}

DirectedGraph* GraphRepository::getDirectedGraph(int id)
{
	auto predicate = [=](DirectedGraph* directedGraph)
	{
		return directedGraph->getId() == id;
	};
	auto result = std::find_if(directedGraphs.begin(), directedGraphs.end(), predicate);
	return result != directedGraphs.end() ? (*result)->clone() : nullptr;
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
