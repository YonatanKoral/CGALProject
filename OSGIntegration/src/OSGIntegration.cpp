// CGALTest.cpp : Defines the entry point for the application.
//

#include "OSGIntegration.h"

int main(int argc, char** argv)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->setCullingActive(false);
	geode->addDrawable(new CEGUIDrawable);
	geode->getOrCreateStateSet()->setAttributeAndModes(new osg::BlendFunc);
	geode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

	osg::ref_ptr<osg::Camera> hudCamera = osgCookBook::createHUDCamera(0, 800, 0, 600);
	hudCamera->setAllowEventFocus(true);
	hudCamera->addChild(geode.get());

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(osgDB::readNodeFile("cow.osg"));
	root->addChild(hudCamera.get());

	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	viewer.addEventHandler(new CEGUIEventHandler(hudCamera.get()));
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
	viewer.addEventHandler(new osgViewer::StatsHandler);
	return viewer.run();
}