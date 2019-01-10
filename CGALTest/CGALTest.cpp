// CGALTest.cpp : Defines the entry point for the application.
//

#include "CGALTest.h"


int main()
{
	Mesh m;
	CGAL::make_icosahedron<Mesh, Point>(m);
	CGAL::draw(m);
	return 0;
}
