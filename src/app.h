#pragma once

#include <vector>

class Task;

class App {
public:
    App();
    ~App();

    void run();

private:
    int showMainMenu();
    void showAllTasks();
    void addTask();

    std::vector<Task*> m_taskList;
};