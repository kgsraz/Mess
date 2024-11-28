#include "User.h"

User::User(const std::string& name, const std::string& login, const std::string& pass)
    : _name(name), _login(login), _pass(pass) {}

void User::save(std::ofstream& out) const {
    out << _name << std::endl;
    out << _login << std::endl;
    out << _pass << std::endl;
}

void User::load(std::ifstream& in) {
    std::getline(in, _name);
    std::getline(in, _login);
    std::getline(in, _pass);
}

std::string User::getLogin() const {
    return _login;
}
