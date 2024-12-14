@echo off
g++ main.cpp -o main.exe
if exist program.exe (
    echo compiled
) else (
    echo error
    exit /b
)
del "%~f0"