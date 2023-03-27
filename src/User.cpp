#include "User.h"

User::User(const std::string& username, const std::string& firstName, const std::string& lastName)
    : m_username(username), m_firstName(firstName), m_lastName(lastName) {}

const std::string& User::getUsername() const {
    return m_username;
}

const std::string& User::getFirstName() const {
    return m_firstName;
}

const std::string& User::getLastName() const {
    return m_lastName;
}
