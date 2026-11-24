@echo off
REM Build script for Windows using MinGW GCC
echo Compiling Railway Tracking System...
gcc -Wall -Wextra -std=c99 -Iinclude src/main.c src/graph.c src/minheap.c src/dijkstra.c -o railway_tracker.exe
if %ERRORLEVEL% equ 0 (
    echo.
    echo ====================================================
    echo Compilation successful! Executable: railway_tracker.exe
    echo Run it using: railway_tracker.exe
    echo ====================================================
) else (
    echo.
    echo [ERROR] Compilation failed. Please check gcc setup.
)
