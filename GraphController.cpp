#include "GraphController.h"
#include <string>
using std::string;

GraphController::GraphController(const string& address, const string& port, GraphService* graphService, EdmondsKarpService* edmondsKarpService, PushRelabelService* pushRelabelService) : BasicController(address, port)
{
    this->graphService = graphService;
    this->edmondsKarpService = edmondsKarpService;
    this->pushRelabelService = pushRelabelService;
}
GraphController::~GraphController()
{
    delete graphService;
    delete edmondsKarpService;
    delete pushRelabelService;
}

void GraphController::initRestOpHandlers() 
{
    listener.support(methods::GET, std::bind(&GraphController::handleGet, this, std::placeholders::_1));
}

void GraphController::handleGet(http_request message)
{
    vector<utility::string_t> path = requestPath(message);
    if (path.empty()) 
    {
        message.reply(status_codes::BadRequest);
    }
    else 
    {
        if (path[0] == to_string_t("graph")) 
        {
            if (path.size() < 2)
            {
                message.reply(status_codes::BadRequest);
                return;
            }
            int id = stoi(path[1]);
            auto graph = graphService->getGraph(id);
            if (graph == nullptr)
            {
                message.reply(status_codes::NotFound);
                return;
            }
            json::value graphJson;
            graphJson[to_string_t("graph")] = json::value::string(to_string_t(graph->toString()));
            message.reply(status_codes::OK, graphJson);
            delete graph;
        }
        else if (path[0] == to_string_t("directed-graph"))
        {
            if (path.size() < 2)
            {
                message.reply(status_codes::BadRequest);
                return;
            }
            int id = stoi(path[1]);
            auto directedGraph = graphService->getDirectedGraph(id);
            if (directedGraph == nullptr)
            {
                message.reply(status_codes::NotFound);
                return;
            }
            json::value graphJson;
            graphJson[to_string_t("directepGraph")] = json::value::string(directedGraph->toString());
            message.reply(status_codes::OK, graphJson);
            delete directedGraph;
        }
        else if(path[0] == to_string_t("edmonds-karp"))
        {
            if (path.size() < 4)
            {
                message.reply(status_codes::BadRequest);
                return;
            }
            int id = stoi(path[1]);
            int source = stoi(path[2]);
            int destination = stoi(path[3]);
            auto graph = graphService->getGraph(id);
            if (graph == nullptr)
            {
                message.reply(status_codes::NotFound);
                return;
            }
            auto result = edmondsKarpService->calculateMaxFlow(graph, source, destination);
            json::value resultJson;
            resultJson[to_string_t("result")] = json::value::number(result);
            message.reply(status_codes::OK, resultJson);
            delete graph;
        }
        else if (path[0] == to_string_t("push-relabel"))
        {
            if (path.size() < 4)
            {
                message.reply(status_codes::BadRequest);
                return;
            }
            int id = stoi(path[1]);
            int source = stoi(path[2]);
            int destination = stoi(path[3]);
            auto directedGraph = graphService->getDirectedGraph(id);
            if (directedGraph == nullptr)
            {
                message.reply(status_codes::NotFound);
                return;
            }
            auto result = pushRelabelService->calculateMaxFlow(directedGraph, source, destination);
            json::value resultJson;
            resultJson[to_string_t("result")] = json::value::number(result);
            message.reply(status_codes::OK, resultJson);
            delete directedGraph;
        }
        else
        {
            message.reply(status_codes::BadRequest);
        }
    }
}