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

CameraManager::CameraManager()
{
    m_Camera = nullptr;
    m_CameraNode = nullptr;
    m_CameraMan = nullptr;
}

CameraManager::~CameraManager()
{
    if (m_CameraNode && m_Camera) m_CameraNode->detachObject(m_Camera);

    if (m_Camera) App::GetSceneManager()->destroyCamera(m_Camera);

    if (m_CameraNode) App::GetSceneManager()->destroySceneNode(m_CameraNode);
    
    if(m_CameraMan)
    {
        // is this correct?
        delete m_CameraMan;
    }
}

void CameraManager::Init()
{
  Ogre::SceneNode* m_CameraNode = App::GetSceneManager()->getRootSceneNode()->createChildSceneNode();
  m_CameraNode->setPosition(200, 300, 200);
  m_CameraNode->setDirection(0,0,-1);
  //m_CameraNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_PARENT);

  // create the camera
  m_Camera = App::GetSceneManager()->createCamera("myCam");
  m_Camera->setNearClipDistance(5); // specific to this sample
  m_Camera->setAutoAspectRatio(true);
  m_CameraNode->attachObject(m_Camera);

  m_CameraMan = new OgreBites::CameraMan(m_CameraNode);
  m_CameraMan->setStyle(OgreBites::CameraStyle::CS_FREELOOK);
  
  // and tell it to render into the main window
  Ogre::Viewport* vp = App::GetAppContext()->getRenderWindow()->addViewport(m_Camera);
  vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
}