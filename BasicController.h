#pragma once
#ifndef BASICCONTROLLER_H_INCLUDED
#define BASICCONTROLLER_H_INCLUDED
#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>
#include <string>
#include <cpprest/http_msg.h>

using namespace web;
using namespace http;
using namespace http::experimental::listener;
using namespace utility::conversions;
using namespace std;

class BasicController
{
public:
	BasicController(const string& address, const string& port);
	~BasicController();
	void setEndpoint(const string& mountPoint);
	string endpoint() const;
	pplx::task<void> accept();
	pplx::task<void> shutdown();

	virtual void initRestOpHandlers() = 0;
	vector<utility::string_t> requestPath(const http_request& message);
	std::map<utility::string_t, utility::string_t> requestQuery(const http_request& message);
protected:
	http_listener listener;
private:
	uri_builder endpointBuilder;
};
#endif // BASICCONTROLLER_H_INCLUDED