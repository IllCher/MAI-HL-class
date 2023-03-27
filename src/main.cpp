#include <iostream>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/Session.h>
#include <Poco/Data/SQLite/Connector.h>
#include <Poco/Data/MySQL/Connector.h>
#include "MyRequestHandlerFactory.h"
#include "Poco/Data/MySQL/Connector.h"

using namespace Poco::Net;
using namespace Poco::Data::Keywords;

int main()
{
    // Register MySQL connector and SQLite connector
    Poco::Data::MySQL::Connector::registerConnector();
    Poco::Data::SQLite::Connector::registerConnector();

    // Initialize database session
    Poco::Data::Session session("MySQL", "host=localhost;user=root;password=;db=mydatabase");


    // Create HTTPServer socket address
    ServerSocket socket(8080);

    // Create HTTPServer
    HTTPServer server(new MyRequestHandlerFactory(session), socket, new HTTPServerParams);

    // Start HTTPServer
    server.start();

    std::cout << "HTTPServer started on port 8080." << std::endl;

    // Wait for termination signal

    // Stop HTTPServer
    server.stop();

    // Unregister connectors
    Poco::Data::MySQL::Connector::unregisterConnector();
    Poco::Data::SQLite::Connector::unregisterConnector();

    return 0;
}

