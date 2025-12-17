@echo off

cmake -S . -B build
cmake --build build --config release
if %errorlevel% neq 0 (
    echo Build failed!
    exit /b %errorlevel%
)

.\build\bin\Release\main.exe