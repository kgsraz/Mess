#pragma once
#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <fstream>
#include <iostream>

class Message {
public:
    Message(const std::string& text, const std::string& sender, const std::string& receiver);

    void save(std::ofstream& out) const;
    void load(std::ifstream& in);

private:
    std::string _text;
    std::string _sender;
    std::string _receiver;
};

#endif // MESSAGE_H
