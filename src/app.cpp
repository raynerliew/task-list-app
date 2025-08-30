#include "app.h"
#include "task.h"

#include <iostream>

App::App() {

}

void App::run() {
    Task testTask;
    testTask.setTitle("Title");
    testTask.setDescription("This is a test.");
    testTask.setDueDate("10-10-2025");
    testTask.show();
}