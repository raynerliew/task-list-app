# task-list-app

Programming language used: C++

This is a simple task list application that allows users to keep track of their tasks.

A task contains:
- Title
- Description
- Due date
- Completion status
- Tags

Users can perform the following actions:
- Show all tasks
- Create a task
- Edit a task
    - Mark this task as completed
    - Edit title
    - Edit description
    - Edit due date
    - Edit tags
- Delete a task
- Create a tag
- Sort tasks
    - By completion status
    - By due date
- Filter tasks
    - By completion status
    - By due date
    - By tag
- Search for tasks by title


## Project Structure
```
task-list-app/
│   .gitignore
│   build.bat
│   README.md
│
├───.vscode
│       c_cpp_properties.json
│       settings.json
│
└───src
        app.cpp
        app.h
        main.cpp
        task.cpp
        task.h
```


## Build Instructions

### Dependencies

- [MinGW-w64](https://www.mingw-w64.org/) or another g++ compiler (C++11 or later)
- Windows 10/11

### Build and Run
1. Open the command prompt and navigate to the project's root directory<br>
`cd task-list-app`

2. In the command prompt, run the following command<br>
`build.bat`

The executable will be created in the build/ folder and launched automatically.


## Testing
Sample tasks and tags can be created for ease of testing by uncommenting the following line in main.cpp<br>
`//taskListApp.createSampleTasksAndTags();`

The app has been tested to handle invalid input, such as entering an invalid option number when navigating the menu and when entering a due date.

The app is also able to handle an empty task list, an empty tag list, as well as prevent the creation of duplicate tags. Additionally when only 1 task exist, the sorting is skipped.


## Showcase

### 30 Second GIF
![Demo](media/demo.gif)

### 7 Minute Video
A video that fully demonstrates the app's features can be found here:<br>
https://github.com/raynerliew/task-list-app/media/demo.mp4
