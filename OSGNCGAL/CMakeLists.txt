﻿# CMakeList.txt : CMake project for CGALTest, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

get_filename_component(PATH_NAME "./" ABSOLUTE)
get_filename_component(SUB_PROJECT_NAME "${PATH_NAME}" NAME)
get_filename_component(${SUB_PROJECT_NAME}_INCLUDE_DIR "${PATH_NAME}/include" ABSOLUTE)
message("Project found: ${SUB_PROJECT_NAME}")

find_package(CGAL REQUIRED COMPONENTS Core)
find_package(OpenSceneGraph 3.6.1 REQUIRED osgDB osgUtil osgText osgGA osgViewer)
# TODO: Add tests and install targets if needed.


INCLUDE(MacroUtils)
message("CGAL found? ${CGAL_FOUND}")
STATIC_OR_DYNAMIC_LINKING()


set(CMAKE_BINARY_DIR "${REPOSITORY_PATH}/build/bin")
  #required to use basic_viewer
   include_directories(
	${OSG_INCLUDE_DIR}
	${Meshing_INCLUDE_DIR}
	${${SUB_PROJECT_NAME}_INCLUDE_DIR}
	
	)
  #create the executable of the application
	# Add source to this project's executable.
	FILE(GLOB SRC_FILES ./src/*.cpp)
	FILE(GLOB H_FILES ./include/*.h)
	add_library(${SUB_PROJECT_NAME} ${LINKING_USER_DEFINED_DYNAMIC_OR_STATIC}  ${SRC_FILES} ${H_FILES})
  #link it with the required CGAL libraries
  target_link_libraries(${SUB_PROJECT_NAME} CGAL::CGAL CGAL::CGAL_Core Meshing)
  SETOUTPUTS(${SUB_PROJECT_NAME} ${REPOSITORY_BUILD_PATH})

  LINK_WITH_VARIABLES(${SUB_PROJECT_NAME}
	OPENTHREADS_LIBRARY
	OSG_LIBRARY
	OSGDB_LIBRARY
	OSGTEXT_LIBRARY
	OSGGA_LIBRARY
	OSGVIEWER_LIBRARY
	OSGUTIL_LIBRARY
)
INCLUDE(ModuleInstall OPTIONAL)
  #target_include_directories(${SUB_PROJECT_NAME} PUBLIC ${${SUB_PROJECT_NAME}_INCLUDE_DIR})
  message("${SUB_PROJECT_NAME} Include directory: ${${SUB_PROJECT_NAME}_INCLUDE_DIR}")