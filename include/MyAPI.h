#ifndef MYAPI_H
#define MYAPI_H

#include <vector>
#include <string>
#include "User.h"
#include "Wall.h"
#include "ChatMessage.h"

class MyAPI {
public:
    User createUser(const std::string& login, const std::string& name, const std::string& surname);
    User findUserByLogin(const std::string& login);
    std::vector<User> findUsersByName(const std::string& name, const std::string& surname);

    void postOnWall(const std::string& login, const std::string& message);
    std::vector<std::string> getWall(const std::string& login);

    void sendMessage(const User& sender, const User& receiver, const std::string& message);
    std::vector<ChatMessage> getMessages(const User& user);

    std::vector<User> users;
    std::vector<Wall> walls;
    std::vector<ChatMessage> messages;

private:

    User findOrCreateUser(const std::string& login, const std::string& name, const std::string& surname);
    Wall findOrCreateWall(const User& user);
};

#endif // MYAPI_H



