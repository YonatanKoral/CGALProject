/* -*-c++-*- OpenSceneGraph Cookbook
 * Chapter 9 Recipe 4
 * Author: Wang Rui <wangray84 at gmail dot com>
*/
#pragma once
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>
#include <osg/Drawable>

class CEGUIDrawable : public osg::Drawable
{
public:
    CEGUIDrawable();
    CEGUIDrawable( const CEGUIDrawable& copy,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY );
    META_Object( osg, CEGUIDrawable );
    
    virtual void drawImplementation( osg::RenderInfo& renderInfo ) const;
    
    void initializeControls();
    bool handleClose( const CEGUI::EventArgs& e );
    
protected:
    virtual ~CEGUIDrawable() {}
    
    mutable double _lastSimulationTime;
    mutable unsigned int _activeContextID;
    mutable bool _initialized;
};

