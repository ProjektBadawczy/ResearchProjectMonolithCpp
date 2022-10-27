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
        if (path[0] == to_string_t("GetGraph"))
        {
            auto queries = requestQuery(message);
            int id = stoi(queries[to_string_t("id")]);
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
        else if (path[0] == to_string_t("GetDirectedGraph"))
        {
            auto queries = requestQuery(message);
            int id = stoi(queries[to_string_t("id")]);
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
        else if(path[0] == to_string_t("GetEdmondsKarpMaxGraphFlow"))
        {
            auto queries = requestQuery(message);
            int id = stoi(queries[to_string_t("id")]);
            int source = stoi(queries[to_string_t("source")]);
            int destination = stoi(queries[to_string_t("destination")]);
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
        else if (path[0] == to_string_t("GetPushRelabelMaxGraphFlow"))
        {
            auto queries = requestQuery(message);
            int id = stoi(queries[to_string_t("id")]);
            int source = stoi(queries[to_string_t("source")]);
            int destination = stoi(queries[to_string_t("destination")]);
            auto graph = graphService->getDirectedGraph(id);
            if (graph == nullptr)
            {
                message.reply(status_codes::NotFound);
                return;
            }
            auto result = pushRelabelService->calculateMaxFlow(graph, source, destination);
            json::value resultJson;
            resultJson[to_string_t("result")] = json::value::number(result);
            message.reply(status_codes::OK, resultJson);
            delete graph;
        }
        else
        {
            message.reply(status_codes::BadRequest);
        }
    }
}