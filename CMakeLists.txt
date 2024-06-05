cmake_minimum_required(VERSION 3.27)
project(AVL_Tree)

set(CMAKE_CXX_STANDARD 14)

# Add source files
set(SOURCES
        src/AVL.cpp
        src/AVL.h
    )


add_executable(AVL_Tree src/main.cpp ${SOURCES})

# Enable testing
enable_testing()

# Add Catch2 using FetchContent
include(FetchContent)

FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.7 # Specify the version you want to use
)

FetchContent_MakeAvailable(catch2)

# Add the test executable
add_executable(tests tests/test_avl.cpp ${SOURCES}
        tests/test_avl.cpp)

# Link Catch2 with the test executable
target_link_libraries(tests PRIVATE Catch2::Catch2)

# Add test cases
add_test(NAME AVLTests COMMAND tests)