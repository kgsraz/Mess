#pragma once
#ifndef USER_H
#define USER_H

#include <string>
#include <fstream>
#include <iostream>

class User {
public:
    User(const std::string& name, const std::string& login, const std::string& pass);

    void save(std::ofstream& out) const;
    void load(std::ifstream& in);

    std::string getLogin() const;

private:
    std::string _name;
    std::string _login;
    std::string _pass;
};

#endif // USER_H
