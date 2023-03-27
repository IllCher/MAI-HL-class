#include "Wall.h"

void Wall::addPost(const std::string& post) {
    m_posts.push_back(post);
}

const std::vector<std::string>& Wall::getPosts() const {
    return m_posts;
}
