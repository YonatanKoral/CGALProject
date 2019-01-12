# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

get_filename_component(FULL_PATH_NAME "./" ABSOLUTE)
get_filename_component(PROJECT_NAME "${FULL_PATH_NAME}" NAME)
project (${PROJECT_NAME})
# Include sub-projects.
add_subdirectory ("CGALTest")
add_subdirectory ("Remeshing")
