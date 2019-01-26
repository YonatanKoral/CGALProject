/* -*-c++-*- OpenSceneGraph Cookbook
 * Chapter 9 Recipe 4
 * Author: Wang Rui <wangray84 at gmail dot com>
*/

#include "CommonFunctions.h"
#include "CEGUIDrawable.h"

CEGUIDrawable::CEGUIDrawable()
:   _lastSimulationTime(0.0), _activeContextID(0), _initialized(false)
{
    setSupportsDisplayList( false );
    setDataVariance( osg::Object::DYNAMIC );
    getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    getOrCreateStateSet()->setMode( GL_DEPTH_TEST, osg::StateAttribute::OFF );
}

CEGUIDrawable::CEGUIDrawable( const CEGUIDrawable& copy,const osg::CopyOp& copyop )
:   osg::Drawable(copy, copyop),
    _lastSimulationTime(copy._lastSimulationTime),
    _activeContextID(copy._activeContextID),
    _initialized(copy._initialized)
{}

void CEGUIDrawable::drawImplementation( osg::RenderInfo& renderInfo ) const
{
    unsigned int contextID = renderInfo.getContextID();
    if ( !_initialized )
    {
        CEGUI::OpenGLRenderer::bootstrapSystem(CEGUI::OpenGLRenderer::TextureTargetType::TTT_NONE);
        if ( !CEGUI::System::getSingletonPtr() ) return;
        
        CEGUI::DefaultResourceProvider* resource =
            static_cast<CEGUI::DefaultResourceProvider*>( CEGUI::System::getSingleton().getResourceProvider() );
        resource->setResourceGroupDirectory( "schemes", "./datafiles/schemes/" );
        resource->setResourceGroupDirectory( "imagesets", "./datafiles/imagesets/" );
        resource->setResourceGroupDirectory( "fonts", "./datafiles/fonts/" );
        resource->setResourceGroupDirectory( "layouts", "./datafiles/layouts/" );
        resource->setResourceGroupDirectory( "looknfeels", "./datafiles/looknfeel/" );
        resource->setResourceGroupDirectory( "lua_scripts", "./datafiles/lua_scripts/" );
        
        CEGUI::ImageManager::setImagesetDefaultResourceGroup( "imagesets" );
        CEGUI::Font::setDefaultResourceGroup( "fonts" );
        CEGUI::Scheme::setDefaultResourceGroup( "schemes" );
        CEGUI::WidgetLookManager::setDefaultResourceGroup( "looknfeels" );
        CEGUI::WindowManager::setDefaultResourceGroup( "layouts" );
        CEGUI::ScriptModule::setDefaultResourceGroup( "lua_scripts" );
        
        const_cast<CEGUIDrawable*>(this)->initializeControls();
        _activeContextID = contextID;
        _initialized = true;
    }
    else if ( contextID==_activeContextID )
    {
        osg::State* state = renderInfo.getState();
        state->disableAllVertexArrays();
        state->disableTexCoordPointer( 0 );
        
        glPushMatrix();
        glPushAttrib( GL_ALL_ATTRIB_BITS );
        
		CEGUI::OpenGLRenderer* renderer = static_cast<CEGUI::OpenGLRenderer*>(
		    CEGUI::System::getSingleton().getRenderer() );
		osg::Viewport* viewport = renderInfo.getCurrentCamera()->getViewport();
		if ( renderer && viewport )
		{
			const CEGUI::Sizef& size = renderer->getDisplaySize();
			if ( size.d_width!=viewport->width() || size.d_height!=viewport->height() )
			{
			    CEGUI::System::getSingleton().notifyDisplaySizeChanged(
			        CEGUI::Sizef(viewport->width(), viewport->height()) );
			}
		}
		
        double currentTime = (state->getFrameStamp() ? state->getFrameStamp()->getSimulationTime() : 0.0);
        CEGUI::System::getSingleton().injectTimePulse( (currentTime - _lastSimulationTime)/1000.0 );
        CEGUI::System::getSingleton().renderAllGUIContexts();
        _lastSimulationTime = currentTime;
        
        glPopAttrib();
        glPopMatrix();
    }
}

void CEGUIDrawable::initializeControls()
{
    
	CEGUI::GUIContext& guiContext = CEGUI::System::getSingleton().getDefaultGUIContext();
	CEGUI::SchemeManager::getSingleton().createFromFile( "TaharezLook.scheme" );
	
    //C.setDefaultMouseCursor( "TaharezLook", "MouseArrow" );
    CEGUI::FontManager::getSingleton().createFromFile( "DejaVuSans-10.font" );
	guiContext.setDefaultFont( "DejaVuSans-10" );
    guiContext.getDefaultFont()->setAutoScaled( CEGUI::AutoScaledMode::ASM_Disabled );
    
    CEGUI::Window* root = CEGUI::WindowManager::getSingleton().createWindow( "DefaultWindow", "Root" );
    guiContext.setRootWindow( root );
    
	CEGUI::FrameWindow *demoWindow = static_cast<CEGUI::FrameWindow*>(
        CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/FrameWindow", "DemoWindow") );
    demoWindow->setPosition( CEGUI::UVector2(cegui_reldim(0.01f), cegui_reldim(0.01f)) );
    demoWindow->setSize( CEGUI::USize(cegui_reldim(0.5f), cegui_reldim(0.3f)) );
    demoWindow->setMinSize( CEGUI::USize(cegui_reldim(0.1f), cegui_reldim(0.1f)) );
    demoWindow->setText( "Example Dialog" );
    
    CEGUI::PushButton* demoButtonOK = static_cast<CEGUI::PushButton*>(
        CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button", "DemoButtonOK") );
    demoButtonOK->setPosition( CEGUI::UVector2(cegui_reldim(0.3f), cegui_reldim(0.75f)) );
    demoButtonOK->setSize( CEGUI::USize(cegui_reldim(0.4f), cegui_reldim(0.15f)) );
    demoButtonOK->setText( "OK" );
    
	demoWindow->subscribeEvent( CEGUI::FrameWindow::EventCloseClicked,
        CEGUI::Event::Subscriber(&CEGUIDrawable::handleClose, this) );
    demoWindow->addChild( demoButtonOK );
    root->addChild( demoWindow );
	guiContext.getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
}

bool CEGUIDrawable::handleClose( const CEGUI::EventArgs& e )
{

	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
	CEGUI::Window* root = context.getRootWindow();
	root->getChild("DemoWindow")->setVisible(false);
	return true;
}
