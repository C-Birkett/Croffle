#include "Camera.h"

#include <OgreApplicationContextBase.h>
#include <OgreSceneManager.h>
#include <OgreColourValue.h>

#include "Application.h"

 Camera::Camera()
 {
    // create root camera node (position)
    Ogre::SceneNode* m_CameraNode = App::GetSceneManager()->getRootSceneNode()->createChildSceneNode();

    // create py nodes
    m_CameraYawNode = m_CameraNode->createChildSceneNode();
    m_CameraPitchNode = m_CameraYawNode->createChildSceneNode();
    m_CameraRollNode = m_CameraPitchNode->createChildSceneNode();

    // create the camera
    m_Camera = App::GetSceneManager()->createCamera("myCam");
    m_Camera->setNearClipDistance(4);
    m_Camera->setFarClipDistance(4000);
    m_Camera->setAutoAspectRatio(true);

    m_CameraRollNode->attachObject(m_Camera);

    // get all on the same page -> Z is up!!!
    m_CameraNode->setFixedYawAxis(true, Ogre::Vector3::UNIT_Z);
    m_CameraYawNode->setFixedYawAxis(true, Ogre::Vector3::UNIT_Z);
    m_CameraPitchNode->setFixedYawAxis(true, Ogre::Vector3::UNIT_Z);
    m_CameraRollNode->setFixedYawAxis(true, Ogre::Vector3::UNIT_Z);

    m_CameraNode->setPosition(Ogre::Vector3::ZERO);
    //m_CameraYawNode->setPosition(Ogre::Vector3::ZERO);
    //m_CameraPitchNode->setPosition(Ogre::Vector3::ZERO);
    //m_CameraRollNode->setPosition(Ogre::Vector3::ZERO);

    //m_CameraNode->setDirection(Ogre::Vector3::ZERO);
    //m_CameraYawNode->setDirection(Ogre::Vector3::ZERO);
    //m_CameraPitchNode->setDirection(Ogre::Vector3::ZERO);
    //m_CameraRollNode->setDirection(Ogre::Vector3::ZERO);

      Ogre::Vector3 pos = m_CameraNode->getPosition();
      Ogre::Vector3 pos2 = m_CameraNode->_getDerivedPosition();
    Pitch(Ogre::Degree(90));
 }

 Camera::~Camera()
 {
    if (m_CameraNode && m_CameraYawNode && m_CameraPitchNode && m_Camera)
    
    m_CameraPitchNode->detachObject(m_Camera);
    App::GetSceneManager()->destroyCamera(m_Camera);

    // hoping this recurses...
    App::GetSceneManager()->destroySceneNode(m_CameraNode);
 }

 void Camera::Yaw(const Ogre::Radian& angle)
 {
    m_CameraYawNode->yaw(angle);
    //m_CameraPitchNode->needUpdate();
    //m_CameraRollNode->needUpdate();
 }

 void Camera::Pitch(const Ogre::Radian& angle)
 {
   Ogre::Vector3 pos = m_CameraNode->getPosition();
    m_CameraPitchNode->pitch(angle);
   pos = m_CameraNode->getPosition();
    //m_CameraRollNode->needUpdate();
 }

 void Camera::Roll(const Ogre::Radian& angle)
 {
    m_CameraRollNode->roll(angle);
 }

 void Camera::Translate(const Ogre::Vector3& translateVector)
 {
   // apply linear transformations in correct order
   Ogre::Vector3 vec = m_CameraYawNode->getOrientation() * m_CameraPitchNode->getOrientation() * translateVector;
   Ogre::Vector3 pos = m_CameraNode->getPosition();
   //m_CameraNode->translate(vec, Ogre::SceneNode::TS_LOCAL);
   m_CameraNode->setPosition(m_CameraNode->getPosition() + vec);

   // not sure if needed?
   //m_CameraYawNode->needUpdate();
   //m_CameraPitchNode->needUpdate();
   //m_CameraRollNode->needUpdate();
 }