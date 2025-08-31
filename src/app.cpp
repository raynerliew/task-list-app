#include "app.h"
#include "task.h"

#include <iostream>
#include <limits>
#include <regex>
#include <sstream>
#include <iomanip>

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
    // For testing
    Task* task1 = new Task();
    task1->setTitle("Task 1");
    task1->setDescription("I am task 1");
    task1->setDueDate("01-01-2025");
    task1->addTag("tag1");
    task1->addTag("tag2");
    task1->addTag("tag3");
    task1->setCompletionStatus(true);
    m_taskList.push_back(task1);

    Task* task2 = new Task();
    task2->setTitle("Task 2");
    task2->setDescription("Task 2 is me");
    task2->setDueDate("02-02-2025");
    task2->addTag("tag2");
    m_taskList.push_back(task2);

    Task* task3 = new Task();
    task3->setTitle("Task 3");
    task3->setDescription("Task 3 here");
    task3->setDueDate("03-03-2020");
    task3->addTag("tag3");
    m_taskList.push_back(task3);

    m_availableTags.push_back("tag1");
    m_availableTags.push_back("tag2");
    m_availableTags.push_back("tag3");
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

        case 6:
            sortTasks();
            break;

        case 7:
            filterTasks();
            break;

        case 8:
            searchTasks();
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

void App::showAllTasks(bool showTaskTitleOnly, bool showHeader) {
    if (showHeader && !showTaskTitleOnly) {
        std::cout << "----- Show all tasks -----\n";
    }

    if (m_taskList.empty()) {
        std::cout << "No tasks have been created yet.\n\n";
        return;
    }

    for (int i = 1; i <= m_taskList.size(); ++i) {
        if (showTaskTitleOnly) {
            std::cout << "[" << i << "] ";
        }

        m_taskList.at(i - 1)->show(showTaskTitleOnly);

        if (!showTaskTitleOnly)
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

    showAllTasks(true);

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
            if (selectedTask->isCompleted()) {
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

            switch (response2) {
                case 1: {
                    if (m_availableTags.empty()) {
                        std::cout << "There are no available tags to add.\n\n";
                        break;
                    }

                    const std::vector<std::string>& selectedTaskTags = selectedTask->getTags();
                    std::vector<std::string> unusedTags;

                    for (const auto& tag : m_availableTags) {
                        // Filter tags that are not added to this task
                        if (std::find(selectedTaskTags.begin(),
                                    selectedTaskTags.end(),
                                    tag) == selectedTaskTags.end()) {
                            unusedTags.push_back(tag);
                        }
                    }

                    if (unusedTags.empty()) {
                        std::cout << "All available tags are already added to this task.\n\n";
                        break;
                    }

                    std::cout << "Available tags to add:\n";
                    for (int i = 1; i <= unusedTags.size(); ++i) {
                        std::cout << "[" << i << "] " << unusedTags.at(i - 1) << "\n";
                    }

                    std::cout << "Enter a number to choose a tag to add to this task: ";
                    int selectedTagIndex = getIntInputInRange(1, unusedTags.size()) - 1;
                    selectedTask->addTag(unusedTags.at(selectedTagIndex));
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

    // Prevent creation of duplicate tags
    if (std::find(m_availableTags.begin(),
                  m_availableTags.end(),
                  newTag) != m_availableTags.end()) {
        std::cout << "\n";
        std::cout << "This tag already exists.\n\n";
        return;
    }

    m_availableTags.push_back(newTag);
    std::cout << "\n";
    std::cout << "The tag has been created.\n\n";
}

void App::sortTasks() {
    std::cout << "----- Sort tasks -----\n";

    std::cout << "\n";
    std::cout << "[1] Sort by completion status\n";
    std::cout << "[2] Sort by due date\n";
    std::cout << "Enter a number to choose your option: ";
    int response = getIntInputInRange(1, 2);

    switch (response) {
        case 1: // Show incomplete tasks first
            std::sort(m_taskList.begin(), m_taskList.end(),
                [](Task* a, Task* b) {
                    return !a->isCompleted() && b->isCompleted();
                });
            break;

        case 2: // Show tasks that are due earlier first
            std::sort(m_taskList.begin(), m_taskList.end(),
                [this](Task* a, Task* b) {
                    std::tm ta = parseDate(a->getDueDate());
                    std::tm tb = parseDate(b->getDueDate());
                    return std::mktime(&ta) < std::mktime(&tb);
                });
            break;
        
        default:
            std::cout << "Sorry, that feature has not been implemented yet.\n\n";
            break;
    }

    std::cout << "The tasks have been sorted.\n";
    
    showAllTasks(false, false);
}

void App::filterTasks() {
    std::cout << "----- Filter tasks -----\n";

    std::cout << "\n";
    std::cout << "[1] Filter by completion status\n";
    std::cout << "[2] Filter by due date\n";
    std::cout << "[3] Filter by tag\n";
    std::cout << "Enter a number to choose your option: ";
    int response = getIntInputInRange(1, 3);
    std::vector<Task*> filteredTasks;

    switch (response) {
        case 1: {
            std::cout << "Filters:\n";
            std::cout << "[1] Incomplete\n";
            std::cout << "[2] Complete\n";
            std::cout << "Enter a number to choose your option: ";
            int response2 = getIntInputInRange(1, 2);
            bool criteria = (response2 == 1) ? false : true;

            for (const auto& task : m_taskList) {
                if (task->isCompleted() == criteria) {
                    filteredTasks.push_back(task);
                }
            }

            break;
        }

        case 2: {
            std::string dueDateFilter = "";
            while (true) {
                std::cout << "Enter due date to filter (DD-MM-YYYY): ";
                std::cin >> dueDateFilter;

                if (isInputCorrectDateFormat(dueDateFilter))
                    break;

                std::cout << "Error: Invalid date format. Please try again.\n";
            }

            for (const auto& task : m_taskList) {
                if (task->getDueDate() == dueDateFilter) {
                    filteredTasks.push_back(task);
                }
            }
            
            break;
        }

        case 3: {
            std::cout << "Filters:\n";
            for (int i = 1; i <= m_availableTags.size(); ++i) {
                std::cout << "[" << i << "] " << m_availableTags.at(i - 1) << "\n";
            }

            std::cout << "Enter a number to choose your option: ";
            int selectedTagIndex = getIntInputInRange(1, m_availableTags.size()) - 1;
            std::string tagFilter = m_availableTags.at(selectedTagIndex);
            
            for (const auto& task : m_taskList) {
                const std::vector<std::string>& tags = task->getTags();
                if (std::find(tags.begin(), tags.end(), tagFilter) != tags.end()) {
                    filteredTasks.push_back(task);
                }
            }

            break;
        }
        
        default:
            std::cout << "Sorry, that feature has not been implemented yet.\n\n";
            break;
    }

    if (filteredTasks.empty()) {
        std::cout << "\n";
        std::cout << "No tasks match this filter\n\n";
        return;
    }

    std::cout << "\n";
    std::cout << "The tasks have been filtered.\n";

    for (int i = 1; i <= filteredTasks.size(); ++i) {
        filteredTasks.at(i - 1)->show();
        std::cout << "\n";
    }
}

void App::searchTasks() {
    std::cout << "----- Search tasks -----\n";

    std::cout << "\n";
    std::cout << "Enter a task title to search for: ";
    std::string titleToSearch;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, titleToSearch);

    // Function to convert characters to lowercase
    auto toLower = [](std::string s) {
        std::transform(s.begin(), s.end(), s.begin(),
                    [](unsigned char c){ return std::tolower(c); });
        return s;
    };

    titleToSearch = toLower(titleToSearch);
    std::vector<Task*> foundTasks;

    for (Task* task : m_taskList) {
        std::string title = toLower(task->getTitle());
        if (title.find(titleToSearch) != std::string::npos) {
            foundTasks.push_back(task);
        }
    }

    if (foundTasks.empty()) {
        std::cout << "\n";
        std::cout << "No tasks match this search query.\n\n";
        return;
    }

    std::cout << "\n";
    std::cout << "The tasks have been searched.\n";

    for (int i = 1; i <= foundTasks.size(); ++i) {
        foundTasks.at(i - 1)->show();
        std::cout << "\n";
    }
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

std::tm App::parseDate(const std::string& date) {
    std::tm tm = {};
    std::istringstream ss(date);
    ss >> std::get_time(&tm, "%d-%m-%Y");
    return tm;
}