#pragma once

#include <string>
#include <vector>

class Task {
public:
    Task();
    ~Task() = default;

    void setDateCreated(const std::string& dateCreated);
    std::string getDateCreated() const;

    void setTimeCreated(const std::string& timeCreated);
    std::string getTimeCreated() const;

    void setDueDate(const std::string& dueDate);
    std::string getDueDate() const;

    void setDescription(const std::string& description);
    std::string getDescription() const;

    void addTag(const std::string& tag);
    void removeTag(const std::string& tag);
    std::vector<std::string> getTags() const;

    void setCompletionStatus(bool completed);
    bool getCompletionStatus() const;

private:
    int m_id;
    std::string m_dateCreated;
    std::string m_timeCreated;
    std::string m_dueDate;
    std::string m_description;
    std::vector<std::string> m_tags;
    bool m_isCompleted;
};