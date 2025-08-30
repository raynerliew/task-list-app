#pragma once

#include <string>
#include <vector>

class Task {
public:
    Task();
    ~Task() = default;

    void show();

    void setTitle(const std::string& title);
    std::string getTitle() const;

    void setDescription(const std::string& description);
    std::string getDescription() const;

    void setDateCreated(const std::string& dateCreated);
    std::string getDateCreated() const;

    void setTimeCreated(const std::string& timeCreated);
    std::string getTimeCreated() const;

    void setDueDate(const std::string& dueDate);
    std::string getDueDate() const;

    void addTag(const std::string& tag);
    void removeTag(const std::string& tag);
    const std::vector<std::string>& getTags() const;

    void setCompletionStatus(bool isCompleted);
    bool getCompletionStatus() const;

private:
    int m_id;
    
    std::string m_title;
    std::string m_description;
    std::string m_dateCreated;
    std::string m_timeCreated;
    std::string m_dueDate;

    std::vector<std::string> m_tags;
    
    bool m_isCompleted;
};