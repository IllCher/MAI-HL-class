#ifndef MYREQUESTHANDLER_H
#define MYREQUESTHANDLER_H

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/URI.h>
#include <string>
#include "MyAPI.h"

class MyRequestHandler : public Poco::Net::HTTPRequestHandler {
public:
    MyRequestHandler(MyAPI& api);
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

private:
    MyAPI& m_api;
};

#endif

