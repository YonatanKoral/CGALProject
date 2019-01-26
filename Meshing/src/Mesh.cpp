// CGALTest.cpp : Defines the entry point for the application.
//

#include "Mesh.h"

namespace Meshing
{
	bool Remesh(Mesh mesh, double target_edge_length, unsigned int nb_iter)
	{
		if (!CGAL::is_triangle_mesh(mesh))
		{
			std::cerr << "Not a valid input file." << std::endl;
			return false;
		}
		std::cout << "Split border...";
		std::vector<edge_descriptor> border;
		PMP::border_halfedges(faces(mesh),
			mesh,
			boost::make_function_output_iterator(halfedge2edge(mesh, border)));
		PMP::split_long_edges(border, target_edge_length, mesh);
		std::cout << "done." << std::endl;
		std::cout << "Start remeshing "
			<< " (" << num_faces(mesh) << " faces)..." << std::endl;
		PMP::isotropic_remeshing(
			faces(mesh),
			target_edge_length,
			mesh,
			PMP::parameters::number_of_iterations(nb_iter)
			.protect_constraints(true)//i.e. protect border, here
		);
		std::cout << "Remeshing done. faces count: " << num_faces(mesh) << std::endl;
		return true;
	}
}