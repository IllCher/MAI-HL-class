#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User(const std::string& username, const std::string& firstName, const std::string& lastName);
    const std::string& getUsername() const;
    const std::string& getFirstName() const;
    const std::string& getLastName() const;

private:
    std::string m_username;
    std::string m_firstName;
    std::string m_lastName;
};

#endif // USER_H
