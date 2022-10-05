#include "DirectedGraph.h"
using namespace utility;
using namespace utility::conversions;
using namespace std;

DirectedGraph::Vertex::Vertex(int i, int w)
{
	this->i = i;
	this->w = w;
}

DirectedGraph::Vertex::Vertex(utility::string_t text)
{
	string_t iName = U("i: ");
	string_t wName = U("w: ");
	size_t pos = 0;
	size_t nextStopPos = 0;
	pos = text.find(iName, pos);
	nextStopPos = text.find(U(","), pos);
	this->i = stoi(text.substr(pos + iName.length(), nextStopPos - (pos + iName.length())));
	pos = text.find(wName, pos);
	nextStopPos = text.find(U("}"), pos);
	this->w = stoi(text.substr(pos + wName.length(), nextStopPos - (pos + wName.length())));
}
DirectedGraph::Vertex::~Vertex()
{

}
string_t DirectedGraph::Vertex::toString()
{
	string_t ret = U("");
	ret += U("{");
	ret += U("i: ");
	ret += to_string_t(to_string(this->i));
	ret += U(",");
	ret += U("w: ");
	ret += to_string_t(to_string(this->w));
	ret += U("}");
	return ret;
}

DirectedGraph::Vertex* DirectedGraph::Vertex::clone()
{
	return new Vertex(this->i, this->w);
}

DirectedGraph::DirectedGraph(int numberOfVertices, int id)
{
	this->id = id;
	this->numberOfVertices = numberOfVertices;
	this->adjacencyList = new list<Vertex*>[numberOfVertices]();
}

DirectedGraph::DirectedGraph(string_t text)
{
	string_t idName = U("id: ");
	string_t numberOfVerticesName = U("numberOfVertices: ");
	string_t adjacencyListName = U("adjacencyList: ");
	size_t pos = 0;
	size_t nextStopPos = 0;
	pos = text.find(idName, pos);
	nextStopPos = text.find(U(","), pos);
	this->id = stoi(text.substr(pos + idName.length(),
		nextStopPos - (pos + idName.length())));
	pos = text.find(numberOfVerticesName, pos);
	nextStopPos = text.find(U(","), pos);
	this->numberOfVertices = stoi(text.substr(pos + numberOfVerticesName.length(),
		nextStopPos - (pos + numberOfVerticesName.length())));
	this->adjacencyList = new list<Vertex*>[numberOfVertices]();
	pos = text.find(adjacencyListName, pos);
	pos += adjacencyListName.length();
	// move after the first opening bracket
	pos += 1;
	string_t vertexText = U("");
	for (int i = 0; i < numberOfVertices; i++)
	{
		while (text[pos] != U(']'))
		{
			// move after the opening bracket or comma
			pos += 1;
			// break if list empty
			if (text[pos] == U(']'))
			{
				break;
			}
			nextStopPos = text.find(U("}"), pos);
			// take whole vertex in text form
			vertexText = text.substr(pos, nextStopPos - pos + 1);
			this->adjacencyList[i].push_back(new Vertex(vertexText));
			// move to the closing bracket or comma
			pos = nextStopPos + 1;
		}
		// move after comma and opening bracket
		pos += 2;
	}
}

DirectedGraph::~DirectedGraph()
{
	for (int i = 0; i < this->numberOfVertices; i++)
	{
		for (Vertex* vertex : this->adjacencyList[i])
		{
			delete vertex;
		}
	}
	delete[] this->adjacencyList;
}

int DirectedGraph::getId()
{
	return this->id;
}

int DirectedGraph::getNumberOfVertices()
{
	return this->numberOfVertices;
}

list<DirectedGraph::Vertex*>* DirectedGraph::getAdjacencyList()
{
	return this->adjacencyList;
}

void DirectedGraph::addEdge(int u, int v, int weight)
{
	this->adjacencyList[u].push_back(new Vertex(v, weight));
}

bool DirectedGraph::hasEdge(int u, int v)
{
	if (u >= this->numberOfVertices)
	{
		return false;
	}
	for (Vertex* vertex : this->adjacencyList[u])
	{
		if (vertex->i == v)
		{
			return true;
		}
	}
	return false;
}

DirectedGraph::Vertex* DirectedGraph::getNeighbour(int u, int v)
{
	for (Vertex* vertex : this->adjacencyList[u])
	{
		if (vertex->i == v)
		{
			return vertex;
		}
	}
	return nullptr;
}

string_t DirectedGraph::toString()
{
	string_t ret = U("");
	ret += U("{");
	ret += U("id: ");
	ret += to_string_t(to_string(this->id));
	ret += U(",");
	ret += U("numberOfVertices: ");
	ret += to_string_t(to_string(this->numberOfVertices));
	ret += U(",");
	ret += U("adjacencyList: ");
	ret += U("[");
	for (int i = 0; i < this->numberOfVertices; i++)
	{
		if (!this->adjacencyList[i].empty())
		{
			ret += U("[");
			for (auto v : this->adjacencyList[i])
			{
				ret += v->toString();
				ret += U(",");
			}
			// switch last comma to closing bracket
			ret[ret.length() - 1] = U(']');
			ret += U(",");
		}
		else
		{
			ret += U("[],");
		}
	}
	// switch last comma to closing bracket
	ret[ret.length() - 1] = U(']');
	ret += U("}");
	return ret;
}

DirectedGraph* DirectedGraph::clone()
{
	auto ret = new DirectedGraph(this->numberOfVertices, this->id);
	for (int u = 0; u < this->numberOfVertices; u++)
	{
		for (auto v : this->adjacencyList[u])
		{
			ret->addEdge(u, v->i, v->w);
		}
	}
	return ret;
}
