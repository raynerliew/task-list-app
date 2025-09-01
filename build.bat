@echo off
if not exist build (
    mkdir build
)

g++ src/*.cpp -o build/task-list-app.exe
.\build\task-list-app.exe