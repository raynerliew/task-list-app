#include "app.h"
#include "task.h"

#include <iostream>
#include <limits> 

App::App() {

}

void App::run() {
    // TODO: Create user
    // ..

    int response = showMainMenu();

    if (response == 0) {
        return;
    }

    Task testTask;
    testTask.setTitle("Title");
    testTask.setDescription("This is a test.");
    testTask.setDueDate("10-10-2025");
    testTask.show();
}

int App::showMainMenu() {
    while (true) {
        std::cout << "Hello! Welcome to task-list-app. Enter a number to choose your option:\n";
        std::cout << "[1] Create a task\n";
        std::cout << "[2] Delete a task\n";
        std::cout << "[3] Edit a task\n";
        std::cout << "[4] Create a tag\n";
        std::cout << "[5] Sort tasks\n";
        std::cout << "[6] Filter tasks\n";
        std::cout << "[7] Search for tasks\n";
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