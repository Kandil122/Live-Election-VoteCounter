#!/bin/bash

echo "Building Live Election Vote Counter GUI Dashboard..."

# Check if Qt6 is available
if ! command -v qmake &> /dev/null; then
    echo "Error: Qt6 not found in PATH"
    echo "Please install Qt6 and add qmake to your PATH"
    echo "Or use Qt Creator to open the CMakeLists.txt file"
    exit 1
fi

# Create build directory
mkdir -p cmake-build-gui
cd cmake-build-gui

# Configure with CMake
echo "Configuring with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release
if [ $? -ne 0 ]; then
    echo "CMake configuration failed"
    exit 1
fi

# Build the project
echo "Building project..."
make -j$(nproc) election_dashboard
if [ $? -ne 0 ]; then
    echo "Build failed"
    exit 1
fi

echo ""
echo "Build completed successfully!"
echo ""
echo "To run the GUI dashboard:"
echo "1. Navigate to cmake-build-gui"
echo "2. Run ./election_dashboard"
echo ""
echo "Note: Make sure Qt6 runtime libraries are available"
echo ""

# Make executable runnable
chmod +x election_dashboard
