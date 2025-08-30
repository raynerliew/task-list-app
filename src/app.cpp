#include "app.h"
#include "task.h"

#include <iostream>
#include <limits>
#include <regex> 

App::App() {

}

App::~App() {
    for (auto task : m_taskList) {
        delete task;
        task = nullptr;
    }

    m_taskList.clear();
}

void App::run() {
    // TODO: Create user
    // ..

    // For testing
    Task* testTask = new Task();
    testTask->setTitle("Test task");
    testTask->setDescription("bla bla bla la la la");
    testTask->setDueDate("01-01-2025");
    m_taskList.push_back(testTask);

    while (true) {
        int response = showMainMenu();

        if (response == 0) {
            break;
        }

        switch (response) {
        case 1:
            showAllTasks();
            break;

        case 2:
            addTask();
            break;

        case 3:
            editTask();
            break;
        
        default:
            std::cout << "Sorry, that feature has not been implemented yet.\n\n";
            break;
        }
    }
}

int App::showMainMenu() {
    while (true) {
        std::cout << "Hello! Welcome to task-list-app. Enter a number to choose your option:\n";
        std::cout << "[1] Show all tasks\n";
        std::cout << "[2] Create a task\n";
        std::cout << "[3] Edit a task\n";
        std::cout << "[4] Delete a task\n";
        std::cout << "[5] Create a tag\n";
        std::cout << "[6] Sort tasks\n";
        std::cout << "[7] Filter tasks\n";
        std::cout << "[8] Search for tasks\n";
        std::cout << "[0] Exit\n";

        return getIntInputInRange(0, 8);
    }
}

void App::showAllTasks(bool showTitleOnly) {
    if (m_taskList.empty()) {
        std::cout << "No tasks have been created yet.\n\n";
    }

    if (!showTitleOnly) {
        std::cout << "----- Show all tasks -----\n";
    }

    for (int i = 1; i <= m_taskList.size(); ++i) {
        if (showTitleOnly) {
            std::cout << "[" << i << "] ";
        }

        m_taskList.at(i - 1)->show(showTitleOnly);

        if (!showTitleOnly)
            std::cout << "\n";
    }
}

void App::addTask() {
    Task* testTask = new Task();

    std::cout << "----- Create a task -----\n";

    std::string title = "";
    std::cout << "Enter title: ";
    std::cin >> title;

    std::string description = "";
    std::cout << "Enter description: ";
    std::cin >> description;

    std::string dueDate = "";
    while (true) {
        // DD-MM-YYYY
        std::regex pattern(R"(^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-(\d{4})$)");

        std::cout << "Enter due date (DD-MM-YYYY): ";
        std::cin >> dueDate;

        if (std::regex_match(dueDate, pattern))
            break;

        std::cout << "Error: Invalid date format. Please try again.\n";
    }

    testTask->setTitle(title);
    testTask->setDescription(description);
    testTask->setDueDate(dueDate);
    m_taskList.push_back(testTask);

    std::cout << "The task has been added.\n\n";
}

void App::editTask() {
    std::cout << "----- Edit a task -----\n";

    const bool showTitleOnly = true;
    showAllTasks(showTitleOnly);
    
    std::cout << "\n";
    std::cout << "Please select a task number to edit: ";
    int selectedTaskIndex = getIntInputInRange(1, m_taskList.size());

    std::cout << "----- Editing task -----\n";
    std::cout << "[1] Mark this task as completed\n";
    std::cout << "[2] Edit title\n";
    std::cout << "[3] Edit description\n";
    std::cout << "[4] Edit due date\n";
    std::cout << "[5] Edit tags\n";
    std::cout << "[0] Back\n";
    std::cout << "Enter a number to choose your option: ";
    int response = getIntInputInRange(0, 5);

    switch (response) {
        case 1: {
            std::cout << "Current title: " << m_taskList.at(selectedTaskIndex)->getTitle() << "\n";
            std::cout << "Please enter a new title: ";
            std::string newTitle = "";
            std::cin >> newTitle;
            std::cout << "The title has been updated.\n\n";
            break;
        }
        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            break;
        
        default:
            std::cout << "Sorry, that feature has not been implemented yet.\n\n";
            break;
    }
}

int App::getIntInputInRange(int min, int max) const {
    while (true) {
        int response = -1;
        std::cin >> response;

        if (std::cin.fail()) {
            // Invalid input, clear the error flag and discard the input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Error: Invalid input. Please enter an integer: ";
            continue;
        }

        if (response < min || response > max) {
            std::cout << "Error: Invalid input. Please enter an integer between " << min << " and " << max << ": ";
            continue;
        }

        std::cout << "\n";
        return response;
    }
}