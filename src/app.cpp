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
    testTask->addTag("work");
    testTask->addTag("test");
    testTask->addTag("hello");
    m_taskList.push_back(testTask);

    m_availableTags.push_back("aaa");
    m_availableTags.push_back("bbb");
    m_availableTags.push_back("ccc");
    // End of testing

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

        case 4:
            deleteTask();
            break;
        
        case 5:
            createTag();
            break;

        default:
            std::cout << "Sorry, that feature has not been implemented yet.\n\n";
            break;
        }
    }
}

int App::showMainMenu() {
    while (true) {
        std::cout << "Hello! Welcome to task-list-app.\n";
        std::cout << "[1] Show all tasks\n";
        std::cout << "[2] Create a task\n";
        std::cout << "[3] Edit a task\n";
        std::cout << "[4] Delete a task\n";
        std::cout << "[5] Create a tag\n";
        std::cout << "[6] Sort tasks\n";
        std::cout << "[7] Filter tasks\n";
        std::cout << "[8] Search for tasks\n";
        std::cout << "[0] Exit\n";
        std::cout << "Enter a number to choose your option: ";

        return getIntInputInRange(0, 8);
    }
}

void App::showAllTasks(bool showTitleOnly) {
    if (!showTitleOnly) {
        std::cout << "----- Show all tasks -----\n";
    }

    if (m_taskList.empty()) {
        std::cout << "No tasks have been created yet.\n\n";
        return;
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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, title);
    testTask->setTitle(title);

    std::string description = "";
    std::cout << "Enter description: ";
    std::getline(std::cin, description);
    testTask->setDescription(description);

    std::string dueDate = "";
    while (true) {
        std::cout << "Enter due date (DD-MM-YYYY): ";
        std::cin >> dueDate;

        if (isInputCorrectDateFormat(dueDate))
            break;

        std::cout << "Error: Invalid date format. Please try again.\n";
    }

    testTask->setDueDate(dueDate);
    m_taskList.push_back(testTask);

    std::cout << "The task has been added.\n\n";
}

// TODO: Make this function smaller
void App::editTask() {
    std::cout << "----- Edit a task -----\n";

    const bool showTitleOnly = true;
    showAllTasks(showTitleOnly);

    if (m_taskList.empty()) {
        return;
    }
    
    std::cout << "Please select a task number to edit: ";
    int selectedTaskIndex = getIntInputInRange(1, m_taskList.size());
    Task* selectedTask = m_taskList.at(selectedTaskIndex - 1);

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
        case 0:
            break;

        case 1: {
            if (selectedTask->getCompletionStatus()) {
                std::cout << "This task is already completed.\n\n";
            } else {
                selectedTask->setCompletionStatus(true);
                std::cout << "This task has been marked as completed. Good job!\n\n";
            }

            break;
        }
        
        case 2: {
            std::cout << "Current title: " << selectedTask->getTitle() << "\n";
            std::cout << "Please enter a new title: ";

            std::string newTitle = "";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, newTitle);

            selectedTask->setTitle(newTitle);
            std::cout << "The title has been updated.\n\n";
            break;
        }

        case 3: {
            std::cout << "Current description: " << selectedTask->getDescription() << "\n";
            std::cout << "Please enter a new description: ";

            std::string newDescription = "";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, newDescription);

            selectedTask->setDescription(newDescription);
            std::cout << "The description has been updated.\n\n";
            break;
        }

        case 4: {
            std::cout << "Current due date: " << selectedTask->getDueDate() << "\n";
            std::cout << "Please enter a new due date (DD-MM-YYYY): ";
            
            std::string newDueDate = "";
            while (true) {
                std::cin >> newDueDate;
                if (isInputCorrectDateFormat(newDueDate)) {
                    break;
                }

                std::cout << "Error: Invalid date format. Please try again.\n";
            }

            selectedTask->setDueDate(newDueDate);
            std::cout << "The due date has been updated.\n\n";
            break;
        }

        case 5: {
            std::cout << "This task has the following tags:\n";
            for (int i = 0; i < selectedTask->getTags().size(); ++i) {
                std::string tag = selectedTask->getTags().at(i);
                std::cout << "<" << tag << ">";

                if (i < selectedTask->getTags().size() - 1) {
                    std::cout << ", ";
                }
            }

            std::cout << "\n\n";
            std::cout << "[1] Add a tag to this task\n";
            std::cout << "[2] Remove a tag from this task\n";
            std::cout << "Enter a number to choose your option: ";
            int response2 = getIntInputInRange(1, 2);

            switch (response2)
            {
            case 1: {
                if (m_availableTags.empty()) {
                    std::cout << "There are no available tags to add.\n\n";
                    break;
                }

                std::cout << "Available tags to add:\n";
                for (int i = 1; i <= m_availableTags.size(); ++i) {
                    std::cout << "[" << i << "] " << m_availableTags.at(i - 1) << "\n";
                }

                // TODO: Prevent user from adding duplicate tags
                // ...

                std::cout << "Enter a number to choose a tag to add to this task: ";
                int selectedTagIndex = getIntInputInRange(1, m_availableTags.size());
                
                selectedTask->addTag(m_availableTags.at(selectedTagIndex - 1));
                std::cout << "The tag has been added to this task.\n\n";
                
                break;
            }

            case 2: {
                if (selectedTask->getTags().empty()) {
                    std::cout << "This task has no tags to remove.\n";
                    break;
                }

                std::cout << "Available tags to remove:\n";
                for (int i = 1; i <= selectedTask->getTags().size(); ++i) {
                    std::cout << "[" << i << "] " << selectedTask->getTags().at(i - 1) << "\n";
                }

                std::cout << "Enter a number to choose a tag to remove from this task: ";
                int selectedTagIndex = getIntInputInRange(1, selectedTask->getTags().size()) - 1;
                selectedTask->removeTag(selectedTask->getTags().at(selectedTagIndex));
                std::cout << "The tag has been removed from this task.\n\n";

                break;
            }

            default:
                break;
            }

            break;
        }
        
        default:
            std::cout << "Sorry, that feature has not been implemented yet.\n\n";
            break;
    }
}

void App::deleteTask() {
    std::cout << "----- Delete a task -----\n";
    
    if (m_taskList.empty()) {
        std::cout << "There are no tasks to delete.\n\n";
        return;
    }

    for (int i = 1; i <= m_taskList.size(); ++i) {
        std::cout << "[" << i << "] " << m_taskList.at(i - 1)->getTitle() << "\n";
    }

    std::cout << "Enter a number to choose a task to delete: ";
    int selectedTaskIndex = getIntInputInRange(1, m_taskList.size()) - 1;
    delete m_taskList[selectedTaskIndex];
    m_taskList.erase(m_taskList.begin() + selectedTaskIndex);

    std::cout << "The task has been deleted.\n\n";
}

void App::createTag() {
    std::cout << "----- Create a tag -----\n";

    std::cout << "Existing tags:\n";
    for (int i = 1; i <= m_availableTags.size(); ++i) {
        std::cout << "[" << i << "] " << m_availableTags.at(i - 1) << "\n";
    }

    std::string newTag = "";
    std::cout << "Enter new tag name: ";
    std::cin >> newTag;

    // TODO: Prevent duplicate tags from existing
    // ...

    m_availableTags.push_back(newTag);
    std::cout << "The tag has been created.\n\n";
}

bool App::isInputCorrectDateFormat(const std::string& input) {
    // DD-MM-YYYY
    std::regex pattern(R"(^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-(\d{4})$)");

    return std::regex_match(input, pattern);
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