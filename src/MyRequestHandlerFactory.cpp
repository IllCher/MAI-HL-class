#include "MyRequestHandlerFactory.h"
#include "MyRequestHandler.h"

MyRequestHandlerFactory::MyRequestHandlerFactory(Poco::Data::Session& session) : session_(session) {}

Poco::Net::HTTPRequestHandler* MyRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
    return new MyRequestHandler(session_);
}
