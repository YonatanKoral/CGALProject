// CGALTest.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/boost/graph/helpers.h>
#include <CGAL/draw_surface_mesh.h>
#include <osg/BlendFunc>
#include <osg/Object>
#include <osg/Drawable>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <iostream>

#include "CommonFunctions.h"
#include "CEGUIDrawable.h"


#include <osg/BlendFunc>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <iostream>


class CEGUIEventHandler : public osgGA::GUIEventHandler
{
public:
	CEGUIEventHandler(osg::Camera* camera) : _camera(camera) {}

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
		/*int x = ea.getX(), y = ea.getY(), width = ea.getWindowWidth(), height = ea.getWindowHeight();
		if (ea.getMouseYOrientation() == osgGA::GUIEventAdapter::Y_INCREASING_UPWARDS)
			y = ea.getWindowHeight() - y;
		if (!CEGUI::System::getSingletonPtr())
			return false;
		auto guiContext = CEGUI::System::getSingleton().getDefaultGUIContext();
		switch (ea.getEventType())
		{
		case osgGA::GUIEventAdapter::PUSH:
			guiContext.injectMousePosition(x, y);
			guiContext.injectMouseButtonDown(convertMouseButton(ea.getButton()));
			break;
		case osgGA::GUIEventAdapter::RELEASE:
			guiContext.injectMousePosition(x, y);
			guiContext.injectMouseButtonUp(convertMouseButton(ea.getButton()));
			break;
		case osgGA::GUIEventAdapter::SCROLL:
			if (ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_DOWN)
				guiContext.injectMouseWheelChange(-1);
			else if (ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_UP)
				guiContext.injectMouseWheelChange(+1);
			break;
		case osgGA::GUIEventAdapter::DRAG:
		case osgGA::GUIEventAdapter::MOVE:
			guiContext.injectMousePosition(x, y);
			break;
		case osgGA::GUIEventAdapter::RESIZE:
			if (_camera.valid())
			{
				_camera->setProjectionMatrix(osg::Matrixd::ortho2D(0.0, width, 0.0, height));
				_camera->setViewport(0.0, 0.0, width, height);
			}
			break;
		default:
			return false;
		}

		CEGUI::Window* rootWindow = guiContext.getRootWindow();
		if (rootWindow)
		{
			CEGUI::Window* anyWindow = rootWindow->getChildAtPosition(CEGUI::Vector2f(x, y));
			if (anyWindow) return true;
		}
		return false;*/

		int x = ea.getX(), y = ea.getY(), width = ea.getWindowWidth(), height = ea.getWindowHeight();
		if (ea.getMouseYOrientation() == osgGA::GUIEventAdapter::Y_INCREASING_UPWARDS)
			y = ea.getWindowHeight() - y;
		if (!CEGUI::System::getSingletonPtr())
			return false;

		CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();

		switch (ea.getEventType())
		{
		case osgGA::GUIEventAdapter::PUSH:
			context.injectMousePosition(x, y);
			context.injectMouseButtonDown(convertMouseButton(ea.getButton()));
			break;
		case osgGA::GUIEventAdapter::RELEASE:
			context.injectMousePosition(x, y);
			context.injectMouseButtonUp(convertMouseButton(ea.getButton()));
			break;
		case osgGA::GUIEventAdapter::SCROLL:
			if (ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_DOWN)
				context.injectMouseWheelChange(-1);
			else if (ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_UP)
				context.injectMouseWheelChange(+1);
			break;
		case osgGA::GUIEventAdapter::DRAG:
		case osgGA::GUIEventAdapter::MOVE:
			context.injectMousePosition(x, y);
			break;
		case osgGA::GUIEventAdapter::RESIZE:
			if (_camera.valid())
			{
				_camera->setProjectionMatrix(osg::Matrixd::ortho2D(0.0, width, 0.0, height));
				_camera->setViewport(0.0, 0.0, width, height);
			}
			break;
		default:
			return false;
		}

		CEGUI::Window* rootWindow = context.getRootWindow();
		if (rootWindow)
		{
			CEGUI::Window* anyWindow = rootWindow->getChildAtPosition(CEGUI::Vector2f(x, y));
			if (anyWindow) return true;
		}
		return false;
	}

protected:
	CEGUI::MouseButton convertMouseButton(int button)
	{
		switch (button)
		{
		case osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON:
			return CEGUI::LeftButton;
		case osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON:
			return CEGUI::MiddleButton;
		case osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON:
			return CEGUI::RightButton;
		default: break;
		}
		return static_cast<CEGUI::MouseButton>(button);
	}

	osg::observer_ptr<osg::Camera> _camera;
};

// TODO: Reference additional headers your program requires here.

