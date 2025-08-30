#include "task.h"

#include <iostream>
#include <algorithm>
#include <ctime>

Task::Task()
    : m_id(-1)
    , m_title("")
    , m_description("")
    , m_dateCreated("")
    , m_timeCreated("")
    , m_dueDate("")
    , m_isCompleted(false) {
    setDateAndTimeCreated();
}

void Task::show(bool showTitleOnly) {
    if (showTitleOnly) {
        std::cout << m_title << "\n";
    }
    else {
        std::cout << "#################################\n";
        std::cout << "<Created on " << m_dateCreated << " at " << m_timeCreated << "> " << m_title << "\n";
        std::cout << m_description << "\n\n";
        std::cout << "Due date: " << m_dueDate << "\n";

        std::cout << "Completion status: " << getCompletionStatusString() << "\n";
        
        std::cout << "Tags: ";
        if (m_tags.empty()) {
            std::cout << "None\n";
        } else {
            for (int i = 0; i < m_tags.size(); ++i) {
                std::cout << "<" << m_tags.at(i) << ">";

                if (i < m_tags.size() - 1) {
                    std::cout << ", ";
                }
            }
            
            std::cout << "\n";
        }

        std::cout << "#################################\n";
    }
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

void Task::setDateAndTimeCreated() {
    std::time_t now = std::time(nullptr);
    std::tm local_tm;
    localtime_s(&local_tm, &now);

    char dateBuffer[11]; // DD-MM-YYYY
    char timeBuffer[9]; // "HH:MM:SS"

    std::strftime(dateBuffer, sizeof(dateBuffer), "%d-%m-%Y", &local_tm);
    std::strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", &local_tm);

    m_dateCreated = dateBuffer;
    m_timeCreated = timeBuffer;
}

std::string Task::getDateCreated() const {
    return m_dateCreated;
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

std::string Task::getCompletionStatusString() const {
    return m_isCompleted ? "Completed" : "Incomplete";
}