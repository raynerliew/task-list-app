#pragma once

#include <string>
#include <vector>

class Task {
public:
    Task();
    ~Task() = default;

    void show(bool showTitleOnly = false);

    void setTitle(const std::string& title);
    std::string getTitle() const;

    void setDescription(const std::string& description);
    std::string getDescription() const;

    std::string getDateCreated() const;
    std::string getTimeCreated() const;

    void setDueDate(const std::string& dueDate);
    std::string getDueDate() const;

    void addTag(const std::string& tag);
    void removeTag(const std::string& tag);
    const std::vector<std::string>& getTags() const;

    void setCompletionStatus(bool isCompleted);
    bool isCompleted() const;
    std::string getCompletionStatusString() const;

private:
    void setDateAndTimeCreated();
    
    std::string m_title;
    std::string m_description;
    std::string m_dateCreated;
    std::string m_timeCreated;
    std::string m_dueDate;

    std::vector<std::string> m_tags;
    
    bool m_isCompleted;
};