#include "MyRequestHandler.h"
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include <Poco/Data/RecordSet.h>
#include <Poco/Data/Statement.h>
#include <Poco/Data/MySQL/MySQLException.h>

MyRequestHandler::MyRequestHandler(Poco::Data::Session& session)
    : session_(session)
{
}

void MyRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
    std::string path = request.getURI();

    if (path == "/create_user") {
        std::string requestBody = getRequestBody(request);
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(requestBody);
        Poco::JSON::Object::Ptr obj = result.extract<Poco::JSON::Object::Ptr>();
        std::string login = obj->getValue<std::string>("login");
        std::string name = obj->getValue<std::string>("name");
        std::string surname = obj->getValue<std::string>("surname");

        try {
            Poco::Data::Statement insert(session_);
            insert << "INSERT INTO users(login, name, surname) VALUES(?, ?, ?)", Poco::Data::Keywords::use(login), Poco::Data::Keywords::use(name), Poco::Data::Keywords::use(surname);
            insert.execute();
            User newUser = api_.createUser(login, name, surname);
            std::string message = "User " + newUser.getUsername() + " created successfully";
            sendResponse(response, message);
        } catch (const Poco::Data::MySQL::MySQLException& e) {
            sendResponse(response, "Error: " + std::string(e.what()));
        }
    } else if (path == "/find_user_by_login") {
        std::string login = request.get("login", "");

        if (login.empty()) {
            sendResponse(response, "Error: missing parameter 'login'");
            return;
        }

        User user = api_.findUserByLogin(login);

        if (user.getUsername().empty()) {
            sendResponse(response, "Error: user not found");
            return;
        }

        Poco::JSON::Object::Ptr obj = new Poco::JSON::Object();
        obj->set("login", user.getUsername());
        obj->set("name", user.getFirstName());
        obj->set("surname", user.getLastName());
        std::stringstream ss;
        obj->stringify(ss);
        sendResponse(response, ss.str());
    } else if (path == "/find_users_by_name") {
        std::string name = request.get("name", "");
        std::string surname = request.get("surname", "");
            if (name.empty() && surname.empty()) {
        sendResponse(response, "Error: missing parameters 'name' or 'surname'");
        return;
    }

    std::vector<User> users = api_.findUsersByName(name, surname);

    if (users.empty()) {
        sendResponse(response, "Error: users not found");
        return;
    }

    Poco::JSON::Array::Ptr arr = new Poco::JSON::Array();

    for (const auto& user : users) {
        Poco::JSON::Object::Ptr obj = new Poco::JSON::Object();
        obj->set("login", user.getUsername());
        obj->set("name", user.getFirstName());
        obj->set("surname", user.getLastName());
        arr->add(obj);
    }

    std::stringstream ss;
    arr->stringify(ss);
    sendResponse(response, ss.str());
} else if (path == "/create_message") {
    std::string requestBody = getRequestBody(request);
    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(requestBody);
    Poco::JSON::Object::Ptr obj = result.extract<Poco::JSON::Object::Ptr>();
    std::string senderLogin = obj->getValue<std::string>("sender");
    std::string recipientLogin = obj->getValue<std::string>("recipient");
    std::string content = obj->getValue<std::string>("content");

    try {
        Poco::Data::Statement insert(session_);
        insert << "INSERT INTO messages(sender_login, recipient_login, content) VALUES(?, ?, ?)", Poco::Data::Keywords::use(senderLogin), Poco::Data::Keywords::use(recipientLogin), Poco::Data::Keywords::use(content);
        insert.execute();
        std::string message = "Message created successfully";
        sendResponse(response, message);
    } catch (const Poco::Data::MySQL::MySQLException& e) {
        sendResponse(response, "Error: " + std::string(e.what()));
    }
} else if (path == "/find_messages_by_recipient") {
    std::string recipientLogin = request.get("recipient", "");

    if (recipientLogin.empty()) {
        sendResponse(response, "Error: missing parameter 'recipient'");
        return;
    }

    std::vector<Message> messages = api_.findMessagesByRecipient(recipientLogin);

    if (messages.empty()) {
        sendResponse(response, "Error: messages not found");
        return;
    }

    Poco::JSON::Array::Ptr arr = new Poco::JSON::Array();

    for (const auto& message : messages) {
        Poco::JSON::Object::Ptr obj = new Poco::JSON::Object();
        obj->set("sender", message.getSender());
        obj->set("recipient", message.getRecipient());
        obj->set("content", message.getContent());
        arr->add(obj);
    }

    std::stringstream ss;
    arr->stringify(ss);
    sendResponse(response, ss.str());
} else {
    sendResponse(response, "Error: unknown path " + path);
}
}

std::string MyRequestHandler::getRequestBody(Poco::Net::HTTPServerRequest& request)
{
std::istream& is = request.stream();
std::string requestBody;
std::string line;

while (std::getline(is, line)) {
    requestBody.append(line);
}

return requestBody;
}


