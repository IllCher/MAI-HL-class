#include "ChatMessage.h"

ChatMessage::ChatMessage(const std::string& sender, const std::string& recipient, const std::string& message)
    : m_sender(sender), m_recipient(recipient), m_message(message) {}

const std::string& ChatMessage::getSender() const {
    return m_sender;
}

const std::string& ChatMessage::getRecipient() const {
    return m_recipient;
}

const std::string& ChatMessage::getMessage() const {
    return m_message;
}
