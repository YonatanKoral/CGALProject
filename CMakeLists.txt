# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

get_filename_component(FULL_PATH_NAME "./" ABSOLUTE)
get_filename_component(REPOSITORY_PATH "../" ABSOLUTE)
get_filename_component(REPOSITORY_BUILD_PATH "${REPOSITORY_PATH}/build" ABSOLUTE)
get_filename_component(PROJECT_NAME "${FULL_PATH_NAME}" NAME)
project (${PROJECT_NAME})

SET(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${FULL_PATH_NAME}/CMakeModules")

INCLUDE(MacroUtils)
# Include sub-projects.
# First for the generic no-config case (e.g. with mingw)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${REPOSITORY_BUILD_PATH}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${REPOSITORY_BUILD_PATH}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${REPOSITORY_BUILD_PATH}/lib )
# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${REPOSITORY_BUILD_PATH}/bin )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${REPOSITORY_BUILD_PATH}/lib )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${REPOSITORY_BUILD_PATH}/lib )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )


set(CMAKE_BINARY_DIR "${REPOSITORY_PATH}/build/bin")
  if(NOT CMAKE_DEBUG_POSTFIX)
	set(CMAKE_DEBUG_POSTFIX d)
  endif()

OPTION(DYNAMIC_LINKING "Set to ON to build the module for dynamic linking.  Use OFF for static." ON)
IF   (DYNAMIC_LINKING)
    SET(LINKING_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
ELSE (DYNAMIC_LINKING)
    SET(LINKING_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
ENDIF(DYNAMIC_LINKING)
add_subdirectory ("Meshing")
add_subdirectory ("Remeshing")
add_subdirectory ("CGALTest")
add_subdirectory ("OSGNCGAL")
add_subdirectory ("OSGIntegration")
