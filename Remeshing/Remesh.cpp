// CGALTest.cpp : Defines the entry point for the application.
//

#include "Remesh.h"


int main()
{
	Mesh m;
	CGAL::make_icosahedron<Mesh, Point>(m);
	Point p1 = Point(0, 0.8, 0);
	CGAL::make_icosahedron<Mesh, Point>(m,p1);

	CGAL::draw(m);
	return 0;
}
