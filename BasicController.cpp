#include "BasicController.h"

BasicController::BasicController(const string& address, const string& port)
{
	this->endpointBuilder.set_host(to_string_t(address));
	this->endpointBuilder.set_port(to_string_t(port));
	this->endpointBuilder.set_scheme(to_string_t("http"));
}

BasicController::~BasicController()
{

}

void BasicController::setEndpoint(const string& mountPoint)
{
	endpointBuilder.set_path(to_string_t(mountPoint));
	listener = http_listener(endpointBuilder.to_uri());
}

pplx::task<void> BasicController::accept()
{
	initRestOpHandlers();
	return listener.open();
}
pplx::task<void> BasicController::shutdown()
{
	return listener.close();
}

std::vector<utility::string_t> BasicController::requestPath(const http_request& message)
{
	auto relativePath = uri::decode(message.relative_uri().path());
	return uri::split_path(relativePath);
}