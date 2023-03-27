#ifndef MYREQUESTHANDLER_H
#define MYREQUESTHANDLER_H

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/MySQL/Connector.h"
#include "MyAPI.h"
using namespace Poco::Data::Keywords;


using namespace Poco::Net;
using namespace Poco::Data;

class MyRequestHandler : public HTTPRequestHandler
{
public:
    MyRequestHandler(MyAPI &api) : m_api(api) {}

    void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) override
    {
        response.setContentType("text/plain");

        std::string method = request.getMethod();
        if (method == "POST" && request.getURI() == "/users")
        {
            handleCreateUser(request, response);
        }
        else if (method == "GET" && request.getURI().find("/users") == 0)
        {
            handleFindUsers(request, response);
        }
        else if (method == "POST" && request.getURI().find("/walls/") == 0)
        {
            handlePostOnWall(request, response);
        }
        else if (method == "GET" && request.getURI().find("/walls/") == 0)
        {
            handleGetWall(request, response);
        }
        else if (method == "POST" && request.getURI().find("/messages/") == 0)
        {
            handleSendMessage(request, response);
        }
        else if (method == "GET" && request.getURI().find("/messages/") == 0)
        {
            handleGetMessages(request, response);
        }
        else
        {
            response.setStatus(HTTPResponse::HTTP_NOT_FOUND);
            response.send();
        }
    }
private:
    MyAPI &m_api;
    MySQL::Connector m_connector;

    void handleCreateUser(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        Session session(MySQL::Connector::KEY, "host=localhost;user=root;password=;db=mydatabase");
        session << "INSERT INTO users(login, name, surname) VALUES(?, ?, ?)",
            use(request.get("login")), use(request.get("name")), use(request.get("surname"));
        response.setStatus(HTTPResponse::HTTP_CREATED);
        response.send();
    }

    void handleFindUsers(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        Session session(MySQL::Connector::KEY, "host=localhost;user=root;password=;db=mydatabase");
        std::string name = request.get("name");
        std::string surname = request.get("surname");
        Statement select(session);
        select << "SELECT login, name, surname FROM users WHERE name = ? AND surname = ?", into(m_api.users), use(name), use(surname), now;
        std::stringstream output;
        for (const auto &user : m_api.users)
        {
            output << user.getUsername() << "," << user.getFirstName() << "," << user.getLastName() << std::endl;
        }
        response.sendBuffer(output.str().data(), output.str().size());
    }

    void handlePostOnWall(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        Session session(MySQL::Connector::KEY, "host=localhost;user=root;password=;db=mydatabase");
        std::string login = request.getURI().substr(std::string("/walls/").size());
        std::string message = request.get("message");
        session << "INSERT INTO wall(login, message) VALUES(?, ?)",
            use(login), use(message);
        response.setStatus(HTTPResponse::HTTP_CREATED);

        response.send();
    }

void handleGetWall(HTTPServerRequest &request, HTTPServerResponse &response)
{
    Session session(MySQL::Connector::KEY, "host=localhost;user=root;password=;db=mydatabase");
    std::string login = request.getURI().substr(std::string("/walls/").size());
    std::vector<std::string> wallPosts = m_api.getWall(login);
    std::stringstream output;
    for (const auto &message : wallPosts)
    {
        output << message << std::endl;
    }
    response.sendBuffer(output.str().data(), output.str().size());
}


    void handleSendMessage(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        Session session(MySQL::Connector::KEY, "host=localhost;user=root;password=;db=mydatabase");
        std::string receiver = request.getURI().substr(std::string("/messages/").size());
        std::string sender = request.get("sender");
        std::string message = request.get("message");
        session << "INSERT INTO messages(sender, receiver, message) VALUES(?, ?, ?)",
            use(sender), use(receiver), use(message);
        response.setStatus(HTTPResponse::HTTP_CREATED);
        response.send();
    }

    void handleGetMessages(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        Session session(MySQL::Connector::KEY, "host=localhost;user=root;password=;db=mydatabase");
        std::string receiver = request.getURI().substr(std::string("/messages/").size());
        Statement select(session);
        select << "SELECT sender, message FROM messages WHERE receiver = ?",
            into(m_api.messages), use(receiver), now;
        std::stringstream output;
        for (const auto &message : m_api.messages)
        {
            output << message.getSender() << ":" << message.getMessage() << std::endl;
        }
        response.sendBuffer(output.str().data(), output.str().size());
    }
};

#endif // MYREQUESTHANDLER_H