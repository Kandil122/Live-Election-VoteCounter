cmake_minimum_required(VERSION 3.10)
project(LiveElectionVoteCounter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(vote_counter
    src/main.cpp
    src/fenwick_tree.cpp
    src/vote_manager.cpp
    src/election_system.cpp
)

# Include directories
target_include_directories(vote_counter PRIVATE include)

# Set compiler flags
if(MSVC)
    target_compile_options(vote_counter PRIVATE /W4)
else()
    target_compile_options(vote_counter PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Create a library target for the core components
add_library(vote_counter_lib
    src/fenwick_tree.cpp
    src/vote_manager.cpp
    src/election_system.cpp
)

target_include_directories(vote_counter_lib PUBLIC include)
target_link_libraries(vote_counter vote_counter_lib)

# GUI Dashboard executable
add_executable(election_dashboard
        src/fenwick_tree.cpp
    src/vote_manager.cpp
    src/election_system.cpp
)
