#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <string>

class ChatMessage {
public:
    ChatMessage(const std::string& sender, const std::string& recipient, const std::string& message);
    const std::string& getSender() const;
    const std::string& getRecipient() const;
    const std::string& getMessage() const;

private:
    std::string m_sender;
    std::string m_recipient;
    std::string m_message;
};

#endif // CHATMESSAGE_H
