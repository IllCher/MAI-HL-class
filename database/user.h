#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Poco/JSON/Object.h"
#include <optional>

namespace database
{
    class User{
        private:
            long _id;
            std::string _first_name;
            std::string _last_name;
            std::string _email;
            std::string _birth_date;
            std::string _login;
            std::string _password;

        public:

            static User fromJSON(const std::string & str);

            long get_id() const;
            const std::string &get_first_name() const;
            const std::string &get_last_name() const;
            const std::string &get_email() const;
            const std::string &get_birth_date() const;
            const std::string &get_login() const;
            const std::string &get_password() const;

            long& id();
            std::string &first_name();
            std::string &last_name();
            std::string &email();
            std::string &birth_date();
            std::string &login();
            std::string &password();

            static void init();
            static std::optional<User> read_by_id(long id);
            static std::optional<long> auth(std::string &login, std::string &password);
            static std::vector<User> search(std::string first_name,std::string last_name);
            static std::vector<User> searchbylogin(std::string login);
            void save_to_mysql();

            Poco::JSON::Object::Ptr toJSON() const;

            static long db_size();

            void save_to_cache();
            void send_to_queue();
            static std::optional<User> read_from_cache_by_id(long id);
    };
}

#endif