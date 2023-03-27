#include "MyAPI.h"

// User endpoints

User MyAPI::createUser(const std::string& login, const std::string& name, const std::string& surname) {
    User newUser(login, name, surname);
    users.push_back(newUser);
    return newUser;
}

User MyAPI::findUserByLogin(const std::string& login) {
    for (auto& user : users) {
        if (user.getUsername() == login) {
            return user;
        }
    }
    return User("", "", "");
}

std::vector<User> MyAPI::findUsersByName(const std::string& name, const std::string& surname) {
    std::vector<User> matchingUsers;
    for (auto& user : users) {
        if (user.getFirstName() == name && user.getLastName() == surname) {
            matchingUsers.push_back(user);
        }
    }
    return matchingUsers;
}

// Wall endpoints

void MyAPI::postOnWall(const std::string& login, const std::string& message) {
    for (auto& wall : walls) {
        if (wall.getUser().getUsername() == login) {
            wall.addPost(message);
            return;
        }
    }
    User user = findUserByLogin(login);
    Wall newWall(user);
    newWall.addPost(message);
    walls.push_back(newWall);
}

std::vector<std::string> MyAPI::getWall(const std::string& login) {
    for (auto& wall : walls) {
        if (wall.getUser().getUsername() == login) {
            return wall.getPosts();
        }
    }
    return std::vector<std::string>();
}

// Chat endpoints

void MyAPI::sendMessage(const User& sender, const User& receiver, const std::string& message) {
    ChatMessage newMessage(sender.getUsername(), receiver.getUsername(), message);
    messages.push_back(newMessage);
}

std::vector<ChatMessage> MyAPI::getMessages(const User& user) {
    std::vector<ChatMessage> userMessages;
    std::string login = user.getUsername();
    for (auto& message : messages) {
        if (message.getSender() == login || message.getRecipient() == login) {
            userMessages.push_back(message);
        }
    }
    return userMessages;
}


// Wall class implementation

Wall::Wall(User user) : m_user(user) {}

void Wall::addPost(const std::string& post) {
    m_posts.push_back(post);
}

