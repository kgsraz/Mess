#include <iostream>
#include <string>
#include <thread>
#include <boost/asio.hpp>
#include "Message.h"

using boost::asio::ip::tcp;

void readMessages(tcp::socket& socket) {
    try {
        while (true) {
            boost::asio::streambuf buffer;
            boost::asio::read_until(socket, buffer, '\n');
            std::istream is(&buffer);
            std::string message;
            std::getline(is, message);
            if (!message.empty()) {
                std::cout << "Received: " << message << std::endl;
            }
        }
    }
    catch (std::exception& e) {
        std::cerr << "Disconnected: " << e.what() << std::endl;
    }
}

int main() {
    try {
        boost::asio::io_context io_context;

        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1", "12345");
        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        std::cout << "Connected to server. You can start chatting!" << std::endl;

        std::thread reader(readMessages, std::ref(socket));

        while (true) {
            std::string message;
            std::getline(std::cin, message);
            message += "\n";
            boost::asio::write(socket, boost::asio::buffer(message));
        }

        reader.join();

    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
