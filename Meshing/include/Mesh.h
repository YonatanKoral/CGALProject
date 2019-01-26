// CGALTest.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/remesh.h>
#include <CGAL/Polygon_mesh_processing/border.h>
#include <boost/function_output_iterator.hpp>
#include <CGAL/boost/graph/helpers.h>
#include <CGAL/draw_surface_mesh.h>
#include "MeshingExport.h"
#include <fstream>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel EK;
typedef CGAL::Surface_mesh<K::Point_3> Mesh;
typedef boost::graph_traits<Mesh>::halfedge_descriptor halfedge_descriptor;
typedef boost::graph_traits<Mesh>::edge_descriptor     edge_descriptor;
typedef boost::graph_traits<Mesh>::vertex_descriptor vertex_descriptor;
typedef Mesh::Property_map<vertex_descriptor, EK::Point_3> Exact_point_map;
typedef Mesh::Property_map<vertex_descriptor, bool> Exact_point_computed;


namespace PMP = CGAL::Polygon_mesh_processing;
namespace params = PMP::parameters;

/*
Exact_point_map mesh1_exact_points =
	mesh1.add_property_map<vertex_descriptor,EK::Point_3>("e:exact_point").first;
  Exact_point_computed mesh1_exact_points_computed =
	mesh1.add_property_map<vertex_descriptor,bool>("e:exact_points_computed").first;
  Exact_point_map mesh2_exact_points =
	mesh2.add_property_map<vertex_descriptor,EK::Point_3>("e:exact_point").first;
  Exact_point_computed mesh2_exact_points_computed =
	mesh2.add_property_map<vertex_descriptor,bool>("e:exact_points_computed").first;
  Coref_point_map mesh1_pm(mesh1_exact_points, mesh1_exact_points_computed, mesh1);
  Coref_point_map mesh2_pm(mesh2_exact_points, mesh2_exact_points_computed, mesh2);

*/




struct halfedge2edge
{
	halfedge2edge(const Mesh& m, std::vector<edge_descriptor>& edges)
		: m_mesh(m), m_edges(edges)
	{}
	void operator()(const halfedge_descriptor& h) const
	{
		m_edges.push_back(edge(h, m_mesh));
	}
	const Mesh& m_mesh;
	std::vector<edge_descriptor>& m_edges;
};

struct Coref_point_map
{
	// typedef for the property map
	typedef boost::property_traits<Exact_point_map>::value_type value_type;
	typedef boost::property_traits<Exact_point_map>::reference reference;
	typedef boost::property_traits<Exact_point_map>::category category;
	typedef boost::property_traits<Exact_point_map>::key_type key_type;
	// exterior references
	Exact_point_computed* exact_point_computed_ptr;
	Exact_point_map* exact_point_ptr;
	Mesh* mesh_ptr;
	Exact_point_computed& exact_point_computed() const
	{
		CGAL_assertion(exact_point_computed_ptr != NULL);
		return *exact_point_computed_ptr;
	}
	Exact_point_map& exact_point() const
	{
		CGAL_assertion(exact_point_ptr != NULL);
		return *exact_point_ptr;
	}
	Mesh& mesh() const
	{
		CGAL_assertion(mesh_ptr != NULL);
		return *mesh_ptr;
	}
	// Converters
	CGAL::Cartesian_converter<K, EK> to_exact;
	CGAL::Cartesian_converter<EK, K> to_input;
	Coref_point_map()
		: exact_point_computed_ptr(NULL)
		, exact_point_ptr(NULL)
		, mesh_ptr(NULL)
	{}
	Coref_point_map(Exact_point_map& ep,
		Exact_point_computed& epc,
		Mesh& m)
		: exact_point_computed_ptr(&epc)
		, exact_point_ptr(&ep)
		, mesh_ptr(&m)
	{}
	friend
		reference get(const Coref_point_map& map, key_type k)
	{
		// create exact point if it does not exist
		if (!map.exact_point_computed()[k]) {
			map.exact_point()[k] = map.to_exact(map.mesh().point(k));
			map.exact_point_computed()[k] = true;
		}
		return map.exact_point()[k];
	}
	friend
		void put(const Coref_point_map& map, key_type k, const EK::Point_3& p)
	{
		map.exact_point_computed()[k] = true;
		map.exact_point()[k] = p;
		// create the input point from the exact one
		map.mesh().point(k) = map.to_input(p);
	}
};
namespace Meshing
{
	bool MESHING_EXPORT Remesh(Mesh mesh, double target_edge_length, unsigned int nb_iter);
}
