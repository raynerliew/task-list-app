#include <iostream>

#include "app.h"

int main() {
    App taskListApp;
    //taskListApp.createSampleTasksAndTags();
    taskListApp.run();

    std::cout << "Thank you for using task-list-app! Goodbye!\n";

    return 0;
}