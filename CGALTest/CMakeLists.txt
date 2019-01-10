# CMakeList.txt : CMake project for CGALTest, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)



# TODO: Add tests and install targets if needed.

if(CGAL_FOUND AND CGAL_Qt5_FOUND)
  #required to use basic_viewer
  add_definitions(-DCGAL_USE_BASIC_VIEWER -DQT_NO_KEYWORDS)
  #create the executable of the application
	# Add source to this project's executable.
	add_executable (CGALTest "CGALTest.cpp" "CGALTest.h")
  #link it with the required CGAL libraries
  target_link_libraries(CGALTest CGAL::CGAL CGAL::CGAL_Qt5 CGAL::CGAL_Core)
else()
  message("ERROR: this program requires CGAL and CGAL_Qt5 and will not be compiled.")
endif()
