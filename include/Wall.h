#ifndef WALL_H
#define WALL_H

#include <vector>
#include <string>
#include "User.h"

class Wall {
public:
    Wall(User user);
    void addPost(const std::string& post);
    const std::vector<std::string>& getPosts() const;
    const User& getUser() const;

private:
    std::vector<std::string> m_posts;
    User m_user;
};

#endif // WALL_H

