#pragma once

#include <string>

class User {
public:
    User(const std::string& name);
    ~User() = default;

    void setName(const std::string& name);
    const std::string getName() const;

private:
    std::string m_name;
};