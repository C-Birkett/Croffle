#include "CameraManager.h"

#include <Ogre.h>
#include <OgreApplicationContextBase.h>
#include <OgreCamera.h>
#include <OgreColourValue.h>
#include <OgreInput.h>
#include <OgreSceneManager.h>
#include <OgreCameraMan.h>

#include "Application.h"
#include "GuiManager.h"
#include "Camera.h"

CameraManager::CameraManager()
{
    m_Camera = nullptr;
}

CameraManager::~CameraManager()
{
    if (m_Camera) delete m_Camera;
}

void CameraManager::Init()
{
    m_Camera = new Camera;
  
    // render into the main window
    Ogre::Viewport* vp = App::GetAppContext()->getRenderWindow()->addViewport(m_Camera->GetCamera());
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
}