#ifndef SERVICE_H_INCLUDED
#define SERVICE_H_INCLUDED
#include "BasicController.h"
#include <vector>
#include "EdmondsKarpService.h"
#include "GraphService.h"


class GraphController : public BasicController {
public:
    GraphController(const string& address, const string& port, GraphService* graphService, EdmondsKarpService* edmondsKarpService);
    ~GraphController();
    void handleGet(http_request message);
    void initRestOpHandlers() override;
private:
    GraphService* graphService;
    EdmondsKarpService* edmondsKarpService;
};

#endif // SERVICE_H_INCLUDED