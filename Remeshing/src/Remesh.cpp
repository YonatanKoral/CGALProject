// CGALTest.cpp : Defines the entry point for the application.
//

#include "Remesh.h"

int main(int argc, char* argv[])
{
	const char* filename = (argc > 1) ? argv[1] : "../data/pig.off";
	std::ifstream input(filename);
	Mesh mesh;
	if (!input || !(input >> mesh) || !CGAL::is_triangle_mesh(mesh)) {
		std::cerr << "Not a valid input file." << std::endl;
		return 1;
	}
	double target_edge_length = 0.1;
	unsigned int nb_iter = 3;
	Meshing::Remesh(mesh, target_edge_length, nb_iter);
	//std::cout << "Split border...";
	//std::vector<edge_descriptor> border;
	//PMP::border_halfedges(faces(mesh),
	//	mesh,
	//	boost::make_function_output_iterator(halfedge2edge(mesh, border)));
	//PMP::split_long_edges(border, target_edge_length, mesh);
	//std::cout << "done." << std::endl;
	//std::cout << "Start remeshing of " << filename
	//	<< " (" << num_faces(mesh) << " faces)..." << std::endl;
	//PMP::isotropic_remeshing(
	//	faces(mesh),
	//	target_edge_length,
	//	mesh,
	//	PMP::parameters::number_of_iterations(nb_iter)
	//	.protect_constraints(true)//i.e. protect border, here
	//);
	//std::cout << "Remeshing done. faces count: " << num_faces(mesh) << std::endl;
	CGAL::draw(mesh);
	return 0;
}
