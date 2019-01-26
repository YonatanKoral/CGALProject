#pragma once
#include "OSGNCGALExport.h"
#include <osg/Geometry>
#include <osg/Object>

#include "osgSupport.h"
namespace CGALSurfaceMesh
{
	class GeometryEngine : public osg::Object
	{
	public:
		META_Object(CGALSurfaceMesh,GeometryEngine)
		GeometryEngine();
		~GeometryEngine();

	private:
		GeometryEngine& operator=(const GeometryEngine &ge) { return *this; }
		GeometryEngine(const GeometryEngine& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) {  }

	};

}