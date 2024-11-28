#include "Message.h"

Message::Message(const std::string& text, const std::string& sender, const std::string& receiver)
    : _text(text), _sender(sender), _receiver(receiver) {}

void Message::save(std::ofstream& out) const {
    out << _text << std::endl;
    out << _sender << std::endl;
    out << _receiver << std::endl;
}

void Message::load(std::ifstream& in) {
    std::getline(in, _text);
    std::getline(in, _sender);
    std::getline(in, _receiver);
}
