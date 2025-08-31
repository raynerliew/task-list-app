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
    void editTaskTitle(Task* selectedTask);
    void editTaskDescription(Task* selectedTask);
    void editTaskDueDate(Task* selectedTask);
    void editTaskTags(Task* selectedTask);

    void deleteTask();
    void createTag();
    void sortTasks();
    void filterTasks();
    void searchTasks();
    
    // Helper functions
    bool isInputCorrectDateFormat(const std::string& input);
    int getIntInputInRange(int min, int max) const;
    std::tm parseDate(const std::string& date);
    
    void createSampleTasksAndTags();

    std::vector<Task*> m_taskList;
    std::vector<std::string> m_availableTags;
};