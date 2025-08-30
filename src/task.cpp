#include "task.h"

#include <iostream>
#include <algorithm>

Task::Task()
    : m_id(-1)
    , m_title("")
    , m_description("")
    , m_dateCreated("")
    , m_timeCreated("")
    , m_dueDate("")
    , m_isCompleted(false) {

}

void Task::show() {
}

void Task::setTitle(const std::string& title) {
    m_title = title;
}

std::string Task::getTitle() const {
    return m_title;
}

void Task::setDescription(const std::string& description) {
    m_description = description;
}

std::string Task::getDescription() const {
    return m_description;
}

void Task::setDateCreated(const std::string& dateCreated) {
    m_dateCreated = dateCreated;
}

std::string Task::getDateCreated() const {
    return m_dateCreated;
}

void Task::setTimeCreated(const std::string& timeCreated) {
    m_timeCreated = timeCreated;
}

std::string Task::getTimeCreated() const {
    return m_timeCreated;
}

void Task::setDueDate(const std::string& dueDate) {
    m_dueDate = dueDate;
}

std::string Task::getDueDate() const {
    return m_dueDate;
}

void Task::addTag(const std::string& tag) {
    // Prevent duplicate tags
    if (std::find(m_tags.begin(), m_tags.end(), tag) != m_tags.end()) {
        std::cout << "Error: This tag already exists\n";
        return;
    }

    m_tags.push_back(tag);
}

void Task::removeTag(const std::string& tag) {
    if (m_tags.empty())
        return;

    m_tags.erase(std::remove(m_tags.begin(), m_tags.end(), tag), m_tags.end());
}

const std::vector<std::string>& Task::getTags() const {
    return m_tags;
}

void Task::setCompletionStatus(bool isCompleted) {
    m_isCompleted = isCompleted;
}

bool Task::getCompletionStatus() const {
    return m_isCompleted;
}