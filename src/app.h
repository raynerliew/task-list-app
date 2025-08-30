#pragma once

#include <vector>

class Task;

class App {
public:
    App();
    ~App() = default;

    void run();

private:
    int showMainMenu();

    std::vector<Task*> m_taskList;
};