#include <cstdio>
#include <iostream> 
#include <fstream> 
#include <vector> 
#include "User.h" 
#include "Message.h" 

void saveUsers(const std::vector<User>& users) {
    std::ofstream out("users.txt", std::ios::app);
    for (const auto& user : users) {
        user.save(out);
    }
}

void loadUsers(std::vector<User>& users) {
    std::ifstream in("users.txt");
    while (in.peek() != EOF) {
        User user("", "", "");
        user.load(in);
        users.push_back(user);
    }
}

int main() {
    std::vector<User> users;
    loadUsers(users);

    // Пример регистрации пользователя 
    User newUser("Alice", "alice", "password123");
    users.push_back(newUser);

    // Сохранение пользователей в файл 
    saveUsers(users);

    // Сообщения, похожим образом можно реализовать 
    std::vector<Message> messages;
    Message newMessage("Hello, Alice!", "Bob", "Alice");
    messages.push_back(newMessage);

    // Сохранение сообщений в файл 
    std::ofstream out("messages.txt", std::ios::app);
    for (const auto& message : messages) {
        message.save(out);
    }

    out.close();

    return 0;
}
