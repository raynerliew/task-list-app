#include <iostream>

#include "app.h"

int main() {
    App taskListApp;
    //taskListApp.createSampleTasksAndTags();
    taskListApp.run();
    taskListApp.close();

    // Wait for user to press any key before quitting
    system("pause");

    return 0;
}