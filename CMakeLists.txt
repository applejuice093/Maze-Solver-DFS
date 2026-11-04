# CMake build, an alternative to the Makefile that also works with MSVC and
# IDEs such as Visual Studio, CLion or VS Code.
#
#   cmake -S . -B build-cmake
#   cmake --build build-cmake
#   ctest --test-dir build-cmake --output-on-failure
cmake_minimum_required(VERSION 3.14)
project(MazeSolverDFS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(maze_core STATIC src/graph.cpp src/dfs.cpp)
target_include_directories(maze_core PUBLIC src)
if(MSVC)
  target_compile_options(maze_core PRIVATE /W4)
else()
  target_compile_options(maze_core PRIVATE -Wall -Wextra)
endif()

add_executable(maze_solver src/main.cpp)
target_link_libraries(maze_solver PRIVATE maze_core)

enable_testing()
add_executable(test_dfs tests/test_dfs.cpp)
target_link_libraries(test_dfs PRIVATE maze_core)
# The tests use assert(), so make sure NDEBUG is never defined for them.
target_compile_options(test_dfs PRIVATE -UNDEBUG)
# Tests open maze/*.edges with relative paths, so run from the source tree.
add_test(NAME unit COMMAND test_dfs WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

find_program(SH_PROGRAM sh)
if(SH_PROGRAM)
  add_test(NAME cli
           COMMAND ${SH_PROGRAM} tests/cli_test.sh $<TARGET_FILE:maze_solver>
           WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()
