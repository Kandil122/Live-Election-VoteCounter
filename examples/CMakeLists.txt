# Example executable
add_executable(sample_election sample_election.cpp)

# Link with the main library
target_link_libraries(sample_election vote_counter_lib)

# Include directories
target_include_directories(sample_election PRIVATE ../include)

# Set compiler flags for examples
if(MSVC)
    target_compile_options(sample_election PRIVATE /W4)
else()
    target_compile_options(sample_election PRIVATE -Wall -Wextra -Wpedantic)
endif()
