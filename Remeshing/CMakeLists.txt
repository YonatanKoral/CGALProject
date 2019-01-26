# CMakeList.txt : CMake project for CGALTest, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
get_filename_component(TGT_BUILD_NAME "../build" ABSOLUTE)
get_filename_component(PATH_NAME "./" ABSOLUTE)
get_filename_component(SUB_PROJECT_NAME "${PATH_NAME}" NAME)
get_filename_component(${SUB_PROJECT_NAME}_INCLUDE_DIR "${PATH_NAME}/include" ABSOLUTE)
message("Project found: ${SUB_PROJECT_NAME}")

find_package(CGAL REQUIRED COMPONENTS Qt5 Core)
# TODO: Add tests and install targets if needed.

INCLUDE(MacroUtils)
if(CGAL_FOUND AND CGAL_Qt5_FOUND)
  #required to use basic_viewer
  
  message("target build name: ${TGT_BUILD_NAME}")
  include_directories(
	${${SUB_PROJECT_NAME}_INCLUDE_DIR} 
	${FULL_PATH_NAME}/Meshing/include)
  add_definitions(-DCGAL_USE_BASIC_VIEWER -DQT_NO_KEYWORDS)
  #create the executable of the application
	# Add source to this project's executable.
	FILE(GLOB SRC_FILES ./src/*.cpp)
	FILE(GLOB H_FILES ./include/*.h)
	add_executable (${SUB_PROJECT_NAME}  ${SRC_FILES} ${H_FILES})
	
  SETOUTPUTS(${SUB_PROJECT_NAME} ${REPOSITORY_BUILD_PATH})
  #link it with the required CGAL libraries
  target_link_libraries(${SUB_PROJECT_NAME} INTERFACE CGAL::CGAL CGAL::CGAL_Qt5 CGAL::CGAL_Core)
   target_link_libraries(${SUB_PROJECT_NAME} PUBLIC Meshing)
  INSTALL(TARGETS ${SUB_PROJECT_NAME} RUNTIME DESTINATION bin )
else()
  message("ERROR: this program requires CGAL and CGAL_Qt5 and will not be compiled for ${SUB_PROJECT_NAME}.")
endif()
