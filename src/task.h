#pragma once

#include <string>
#include <vector>

class Task {
public:
    Task();
    ~Task() = default;

private:
    int m_id;
    std::string m_dateCreated;
    std::string m_timeCreated;
    std::string m_dueDate;
    std::string m_description;
    std::vector<std::string> m_tags;
    bool m_isCompleted;
};