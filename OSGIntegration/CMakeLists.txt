# CMakeList.txt : CMake project for CGALTest, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

get_filename_component(PATH_NAME "./" ABSOLUTE)
get_filename_component(SUB_PROJECT_NAME "${PATH_NAME}" NAME)
get_filename_component(${SUB_PROJECT_NAME}_INCLUDE_DIR "${PATH_NAME}/include" ABSOLUTE)
message("Project found: ${SUB_PROJECT_NAME}")
find_package(OpenGL)
find_package(CGAL REQUIRED COMPONENTS Qt5 Core)
find_package(OpenSceneGraph 3.6.1 REQUIRED osgDB osgUtil osgText osgGA osgViewer)

find_package(CEGUI REQUIRED)

# TODO: Add tests and install targets if needed.
# use this macro for linking with libraries that come from Findxxxx commands
# this adds automatically "optimized" and "debug" information for cmake 

if (CEGUI_FOUND)
  message("CEGUI found at ${CEGUI_INCLUDE_DIR}, gl component ${CEGUI_OpenGLRenderer_INCLUDE_DIRS}")
  
endif()
INCLUDE(MacroUtils)
if(CGAL_FOUND AND CGAL_Qt5_FOUND)
  #required to use basic_viewer
  #set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${REPOSITORY_BUILD_PATH}/lib)
	#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${REPOSITORY_BUILD_PATH}/lib)
	#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${REPOSITORY_BUILD_PATH}/bin)
set(CMAKE_BINARY_DIR "${REPOSITORY_PATH}/build/bin")
  #create the executable of the application
	# Add source to this project's executable.
	#include_directories(${${SUB_PROJECT_NAME}_INCLUDE_DIR})

	get_filename_component(CEGUI_DEPENDENCIES_INCLUDE_DIR "${CEGUI_INCLUDE_DIR}/../dependencies/include" ABSOLUTE)
	message("CEGUI_DEPENDENCIES_INCLUDE_DIR: ${CEGUI_DEPENDENCIES_INCLUDE_DIR}")
	include_directories(
	${CEGUI_DEPENDENCIES_INCLUDE_DIR}
	${CEGUI_OpenGLRenderer_INCLUDE_DIRS}
	${CEGUI_INCLUDE_DIR}
	${OSG_INCLUDE_DIR}
	${OPENGL_INCLUDE_DIR}
	./include
	)
	FILE(GLOB SRC_FILES ./src/*.cpp)
	FILE(GLOB H_FILES ./include/*.h)
	add_executable (${SUB_PROJECT_NAME} ${SRC_FILES} ${H_FILES})
  SETOUTPUTS(${SUB_PROJECT_NAME} ${REPOSITORY_BUILD_PATH})
  #link it with the required CGAL libraries
  target_link_libraries(${SUB_PROJECT_NAME} CGAL::CGAL CGAL::CGAL_Qt5 CGAL::CGAL_Core ${CEGUI_OpenGLRenderer_LIBRARY} ${CEGUI_GL_LIBRARY} ${CEGUI_LIBRARY} ${OPENGL_gl_LIBRARY})
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
else()
  message("ERROR: this program requires CGAL and CGAL_Qt5 and will not be compiled for ${SUB_PROJECT_NAME}.")
endif()
