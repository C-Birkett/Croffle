#pragma once

#include <Ogre.h>
#include <OgreCameraMan.h>
#include <OgreInput.h>
#include <OgreSceneNode.h>

class CameraManager
{
public:
    CameraManager();
    ~CameraManager();
    
    Ogre::Camera*       m_Camera;
    Ogre::SceneNode*    m_CameraNode;
    OgreBites::CameraMan*   m_CameraMan;

    void Init();

private:
        

};