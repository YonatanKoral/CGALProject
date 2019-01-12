# CMakeList.txt : CMake project for CGALTest, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

get_filename_component(PATH_NAME "./" ABSOLUTE)
get_filename_component(PROJECT_NAME "${PATH_NAME}" NAME)
message("Project found: ${PROJECT_NAME}")
project(${PROJECT_NAME})

find_package(CGAL REQUIRED COMPONENTS Qt5 Core)
# TODO: Add tests and install targets if needed.

if(CGAL_FOUND AND CGAL_Qt5_FOUND)
  #required to use basic_viewer
  add_definitions(-DCGAL_USE_BASIC_VIEWER -DQT_NO_KEYWORDS)
  #create the executable of the application
	# Add source to this project's executable.
	FILE(GLOB SRC_FILES ./*.cpp)
	FILE(GLOB H_FILES ./*.h)
	add_executable (${PROJECT_NAME}  ${SRC_FILES} ${H_FILES})
  #link it with the required CGAL libraries
  target_link_libraries(${PROJECT_NAME} CGAL::CGAL CGAL::CGAL_Qt5 CGAL::CGAL_Core)
else()
  message("ERROR: this program requires CGAL and CGAL_Qt5 and will not be compiled for ${PROJECT_NAME}.")
endif()
