# CMakeList.txt : CMake project for CGALTest, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

get_filename_component(PATH_NAME "./" ABSOLUTE)
get_filename_component(SUB_PROJECT_NAME "${PATH_NAME}" NAME)
get_filename_component(${SUB_PROJECT_NAME}_INCLUDE_DIR "${PATH_NAME}/include" ABSOLUTE)
message("Project found: ${SUB_PROJECT_NAME}")

find_package(CGAL REQUIRED COMPONENTS Qt5 Core)
# TODO: Add tests and install targets if needed.


INCLUDE(MacroUtils)
STATIC_OR_DYNAMIC_LINKING()
message("CGAL found? ${CGAL_FOUND}, cgal qt5 found? ${CGAL_Qt5_FOUND}")
if(CGAL_FOUND AND CGAL_Qt5_FOUND)
  #required to use basic_viewer
   include_directories(
	${${SUB_PROJECT_NAME}_INCLUDE_DIR})
  add_definitions(-DCGAL_USE_BASIC_VIEWER -DQT_NO_KEYWORDS)
  #create the executable of the application
	# Add source to this project's executable.
	FILE(GLOB SRC_FILES ./src/*.cpp)
	FILE(GLOB H_FILES ./include/*.h)
	add_library(${SUB_PROJECT_NAME} ${LINKING_USER_DEFINED_DYNAMIC_OR_STATIC}  ${SRC_FILES} ${H_FILES})
  #link it with the required CGAL libraries
  target_link_libraries(${SUB_PROJECT_NAME} CGAL::CGAL CGAL::CGAL_Qt5 CGAL::CGAL_Core)
  SETOUTPUTS(${SUB_PROJECT_NAME} ${REPOSITORY_BUILD_PATH})
  #target_include_directories(${SUB_PROJECT_NAME} PUBLIC ${${SUB_PROJECT_NAME}_INCLUDE_DIR})
  message("${SUB_PROJECT_NAME} Include directory: ${${SUB_PROJECT_NAME}_INCLUDE_DIR}")
else()
  message("ERROR: this program requires CGAL and CGAL_Qt5 and will not be compiled for ${SUB_PROJECT_NAME}.")
endif()
