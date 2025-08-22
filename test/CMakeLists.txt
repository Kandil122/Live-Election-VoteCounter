# Test executable
add_executable(test_election test_election.cpp)

# Link with the main library
target_link_libraries(test_election vote_counter_lib)

# Include directories
target_include_directories(test_election PRIVATE ../include)

# Set compiler flags for tests
if(MSVC)
    target_compile_options(test_election PRIVATE /W4)
else()
    target_compile_options(test_election PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Add test to CTest
add_test(NAME ElectionSystemTest COMMAND test_election)
