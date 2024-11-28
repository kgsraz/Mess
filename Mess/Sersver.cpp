#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <boost/asio.hpp>
#include "Message.h"

using boost::asio::ip::tcp;

std::vector<std::shared_ptr<tcp::socket>> clients;

void broadcastMessage(const std::string& message) {
    for (auto& client : clients) {
        boost::asio::write(*client, boost::asio::buffer(message));
    }
}

void handleClient(std::shared_ptr<tcp::socket> clientSocket) {
    try {
        while (true) {
            boost::asio::streambuf buffer;
            boost::asio::read_until(*clientSocket, buffer, '\n');
            std::istream is(&buffer);
            std::string message;
            std::getline(is, message);

            if (message.empty()) continue;

            std::cout << "Received message: " << message << std::endl;
            broadcastMessage(message);
        }
    }
    catch (std::exception& e) {
        std::cerr << "Client disconnected: " << e.what() << std::endl;
    }
}

int main() {
    try {
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));

        std::cout << "Server started, waiting for clients..." << std::endl;

        while (true) {
            auto clientSocket = std::make_shared<tcp::socket>(io_context);
            acceptor.accept(*clientSocket);

            std::cout << "New client connected" << std::endl;
            clients.push_back(clientSocket);

            std::thread(handleClient, clientSocket).detach();
        }

    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
