#ifndef CHAT_H
#define CHAT_H

#include <string>
#include <vector>
#include "Poco/JSON/Object.h"
#include <optional>

namespace database
{
    class Chat{
    private:
        long _id;
        long _receiver;
        long _sender;
        std::string _message;

    public:

        static Chat fromJSON(const std::string & str);

        long get_id() const;
        // const;
        //const long &get_sender() const;
        // const std::string &get_message() const;

        long& id();
        long &receiver_id();
        long &sender_id();
        std::string &message();

        static void init();
        static std::optional<Chat> read_by_id(long id);
        static std::vector<Chat> read_all();
        static std::optional<Chat> read_by_receiver(long receiver);
        void save_to_mysql();

        Poco::JSON::Object::Ptr toJSON() const;

    };
}

#endif
