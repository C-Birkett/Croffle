#pragma once

#include <Ogre.h>
#include <OgreSceneNode.h>

// quake style camera
// separated pitch yaw and roll nodes to avoid gimball lock
class Camera 
{
public:
    Camera();
    ~Camera();

    Ogre::Camera* GetCamera() {return m_Camera;}
    void Yaw(const Ogre::Radian& angle);
    void Pitch(const Ogre::Radian& angle);
    void Roll(const Ogre::Radian& angle);

    void Translate(const Ogre::Vector3& translateVector);

    Ogre::Matrix3 getLocalAxes() {return m_CameraNode->getLocalAxes();}

private:
    // nodes in order
    Ogre::SceneNode*    m_CameraNode;
    Ogre::SceneNode*    m_CameraYawNode;
    Ogre::SceneNode*    m_CameraPitchNode;
    Ogre::SceneNode*    m_CameraRollNode;
    Ogre::Camera*       m_Camera; // can roll camera directlty
};