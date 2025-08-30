#include "user.h"

User::User(const std::string& name)
    : m_name(name) {

}

void User::setName(const std::string& name) {
    m_name = name;
}

std::string User::getName() const {
    return m_name;
}