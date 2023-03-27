#ifndef MYREQUESTHANDLER_H
#define MYREQUESTHANDLER_H

#include <string>
#include <vector>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Data/Session.h>

#include "MyAPI.h"

class MyRequestHandler : public Poco::Net::HTTPRequestHandler {
public:
    MyRequestHandler(Poco::Data::Session& session);

    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;

private:
    MyAPI api_;
    Poco::Data::Session& session_;

    std::string getRequestBody(Poco::Net::HTTPServerRequest& request);
    void sendResponse(Poco::Net::HTTPServerResponse& response, const std::string& message);
};

#endif // MYREQUESTHANDLER_H



