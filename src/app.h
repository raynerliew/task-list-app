#pragma once

#include <string>
#include <vector>

class Task;

class App {
public:
    App();
    ~App();

    void run();

private:
    int showMainMenu();
    void showAllTasks(bool showTitleOnly = false);
    void addTask();
    void editTask();

    // Helper functions
    bool isInputCorrectDateFormat(const std::string& input);
    int getIntInputInRange(int min, int max) const;

    std::vector<Task*> m_taskList;
    std::vector<std::string> m_availableTags;
};