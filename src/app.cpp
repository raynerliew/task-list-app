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

    while (true) {
        int response = showMainMenu();

        if (response == 0) {
            break;
        }

        switch (response)
        {
        case 1:
            showAllTasks();
            break;

        case 2:
            addTask();
            break;
        
        default:
            std::cout << "That feature has not been implemented yet.\n\n";
            break;
        }
    }
}

int App::showMainMenu() {
    while (true) {
        std::cout << "Hello! Welcome to task-list-app. Enter a number to choose your option:\n";
        std::cout << "[1] Show all tasks\n";
        std::cout << "[2] Create a task\n";
        std::cout << "[3] Delete a task\n";
        std::cout << "[4] Edit a task\n";
        std::cout << "[5] Create a tag\n";
        std::cout << "[6] Sort tasks\n";
        std::cout << "[7] Filter tasks\n";
        std::cout << "[8] Search for tasks\n";
        std::cout << "[0] Exit\n";

        int response = -1;
        std::cin >> response;

        if (std::cin.fail()) {
            // Invalid input, clear the error flag and discard the input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Error: Invalid input. Please enter an integer.\n\n";
            continue;
        }

        if (response < 0 || response > 7) {
            std::cout << "Error: Invalid input. Please enter an integer between 1 and 7.\n\n";
            continue;
        }

        return response;
    }
}

void App::showAllTasks() {
    if (m_taskList.empty()) {
        std::cout << "No tasks have been created yet.\n\n";
    }

    for (auto task : m_taskList) {
        task->show();
        std::cout << "\n";
    }
}

void App::addTask() {
    Task* testTask = new Task();

    std::cout << "----- Create a task -----\n";

    std::string title;
    std::cout << "Enter title: ";
    std::cin >> title;

    std::string description;
    std::cout << "Enter description: ";
    std::cin >> description;

    std::string dueDate;
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