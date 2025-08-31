#pragma once

#include <string>
#include <vector>
#include <ctime>

class Task;

class App {
public:
    App();
    ~App();

    void run();

private:
    int showMainMenu();
    void showAllTasks(bool showTaskTitleOnly = false, bool showHeader = true);
    void addTask();
    void editTask();
    void deleteTask();
    void createTag();
    void sortTasks();

    // Helper functions
    bool isInputCorrectDateFormat(const std::string& input);
    int getIntInputInRange(int min, int max) const;
    std::tm parseDate(const std::string& date);

    std::vector<Task*> m_taskList;
    std::vector<std::string> m_availableTags;
};