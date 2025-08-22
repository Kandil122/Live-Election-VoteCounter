@echo off
echo Building Live Election Vote Counter GUI Dashboard...

REM Check if Qt6 is available
where qmake >nul 2>nul
if %errorlevel% neq 0 (
    echo Error: Qt6 not found in PATH
    echo Please install Qt6 and add qmake to your PATH
    echo Or use Qt Creator to open the CMakeLists.txt file
    pause
    exit /b 1
)

REM Create build directory
if not exist "cmake-build-gui" mkdir cmake-build-gui
cd cmake-build-gui

REM Configure with CMake
echo Configuring with CMake...
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release
if %errorlevel% neq 0 (
    echo CMake configuration failed
    pause
    exit /b 1
)

REM Build the project
echo Building project...
cmake --build . --config Release --target election_dashboard
if %errorlevel% neq 0 (
    echo Build failed
    pause
    exit /b 1
)

echo.
echo Build completed successfully!
echo.
echo To run the GUI dashboard:
echo 1. Navigate to cmake-build-gui\Release
echo 2. Run election_dashboard.exe
echo.
echo Note: Make sure Qt6 runtime libraries are available
echo.

pause
