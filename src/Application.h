#pragma once

#include "GuiManager.h"
#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreResourceGroupManager.h>
#include <OgreSceneManager.h>

class GuiManager;
class KeypressManager;
class CameraManager;

namespace App
{
  // Globals:
  
  // control
  bool Init();
  void StartRendering();
  void Close();
  
  // access
  OgreBites::ApplicationContext*  GetAppContext();
  Ogre::SceneManager*             GetSceneManager();
  GuiManager*                     GetGuiManager();
  KeypressManager*                GetKeypressManager();
  CameraManager*                  GetCameraManaager();
}