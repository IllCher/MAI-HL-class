#ifndef MYREQUESTHANDLERFACTORY_H
#define MYREQUESTHANDLERFACTORY_H

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Data/Session.h>

class MyRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
    MyRequestHandlerFactory(Poco::Data::Session& session);

    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override;

private:
    Poco::Data::Session& session_;
};

#endif // MYREQUESTHANDLERFACTORY_H





