#!/bin/bash

echo "Building Live Election Vote Counter..."
echo

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Configure with CMake
echo "Configuring with CMake..."
cmake ..
if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    exit 1
fi

# Build the project
echo "Building project..."
make -j$(nproc)
if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo
echo "Build completed successfully!"
echo
echo "To run the application:"
echo "  ./vote_counter"
echo
echo "To run tests:"
echo "  ./test_election"
echo

# Make the scripts executable
chmod +x vote_counter
chmod +x test_election
