#pragma once
#include <list>
#include <cpprest/http_msg.h>

class DirectedGraph
{
public:
	struct Vertex
	{
		int i;
		int w;
		Vertex(int i, int w);
		Vertex(utility::string_t text);
		~Vertex();
		utility::string_t toString();
		Vertex* clone();
	};
	DirectedGraph(int numberOfVertices, int id);
	DirectedGraph(utility::string_t text);
	~DirectedGraph();
	int getId();
	int getNumberOfVertices();
	std::list<Vertex*>* getAdjacencyList();
	void addEdge(int u, int v, int weight);
	bool hasEdge(int u, int v);
	Vertex* getNeighbour(int u, int v);
	utility::string_t toString();
	DirectedGraph* clone();
private:
	int numberOfVertices;
	int id;
	std::list<Vertex*>* adjacencyList;
};
