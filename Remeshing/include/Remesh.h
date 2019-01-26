// CGALTest.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/remesh.h>
#include <CGAL/Polygon_mesh_processing/border.h>
#include <boost/function_output_iterator.hpp>
#include <CGAL/boost/graph/helpers.h>
#include <CGAL/draw_surface_mesh.h>
#include "Mesh.h"
#include <fstream>
#include <vector>
//typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Surface_mesh<K::Point_3> Mesh;
//typedef boost::graph_traits<Mesh>::halfedge_descriptor halfedge_descriptor;
//typedef boost::graph_traits<Mesh>::edge_descriptor     edge_descriptor;
//namespace PMP = CGAL::Polygon_mesh_processing;
//struct halfedge2edge
//{
//	halfedge2edge(const Mesh& m, std::vector<edge_descriptor>& edges)
//		: m_mesh(m), m_edges(edges)
//	{}
//	void operator()(const halfedge_descriptor& h) const
//	{
//		m_edges.push_back(edge(h, m_mesh));
//	}
//	const Mesh& m_mesh;
//	std::vector<edge_descriptor>& m_edges;
//};
