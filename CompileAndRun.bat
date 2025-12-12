@echo off

cmake --build build
if %errorlevel% neq 0 (
    echo Build failed!
    exit /b %errorlevel%
)

.\build\bin\Debug\main.exe