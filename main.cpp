#include "GraphController.h"
#include "GraphRepository.h"
#include "GraphService.h"
#include "EdmondsKarpService.h"
#include "BFSService.h"
#include "PushRelabelService.h"
#include "KeyboardInterruptHandler.h"
#include "Defines.h"

int main()
{
	auto graphRepository = new GraphRepository();
	auto graphService = new GraphService(graphRepository);
	auto bfsService = new BFSService();
	auto edmondsKarpService = new EdmondsKarpService(bfsService);
	auto pushRelabelService = new PushRelabelService();
	GraphController serv(ADDRESS, "8080", graphService, edmondsKarpService, pushRelabelService);
	serv.setEndpoint("/api");
	serv.accept().wait();

	return KeyboardInterruptHandler::handleKeyboardInterrupt();
}