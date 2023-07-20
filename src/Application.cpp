#include "Application.h"

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreApplicationContextBase.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreMeshManager.h>
#include <OgrePrerequisites.h>
#include <OgreResourceGroupManager.h>
#include <OgreSceneNode.h>
#include <OgreImGuiOverlay.h>
#include <OgreOverlaySystem.h>

#include <OgreTrays.h>
#include <imgui.h>

#include <cassert>
#include <memory>

#include "KeypressManager.h"
#include "CameraManager.h"
#include "GuiManager.h"

namespace App 
{
  
  // global objects
  static OgreBites::ApplicationContext  g_AppContext("OgreTest");
  static Ogre::SceneManager*            g_SceneManager;
  static KeypressManager*               g_KeypressManager;
  static CameraManager*                 g_CameraManager;
  static GuiManager*                    g_GuiManager;
  //static InputManager*                  g_InputManager;
  static OgreBites::InputListenerChain* g_InputChain;

  // global access
  OgreBites::ApplicationContext*  GetAppContext() {return &g_AppContext;}
  Ogre::SceneManager*             GetSceneManager() {return g_SceneManager;}
  KeypressManager*                GetKeypressManager() {return g_KeypressManager;}  
  CameraManager*                  GetCameraManager() {return g_CameraManager;}
  GuiManager*                     GetGuiManager() {return g_GuiManager;}

  // Factories
  KeypressManager* CreateKeypressManager()
  {
    assert(!g_KeypressManager);
    
    g_KeypressManager = new KeypressManager;
    
    return g_KeypressManager;
  }

  CameraManager* CreateCameraManager()
  {
    assert(!g_CameraManager);
    
    g_CameraManager = new CameraManager;
    g_CameraManager->Init();

    return g_CameraManager;
  }
  
  GuiManager* CreateGuiManager()
  {
    assert(!g_GuiManager);
    
    g_GuiManager = new GuiManager;
    g_GuiManager->Init();
    
    return g_GuiManager;
  }

  // app control
  void CreateTestScene();

  bool Init()
  {
    bool success = true;

    // create root
    g_AppContext.createRoot();

    if (!g_AppContext.oneTimeConfig())
    {
      return false;
    }

    // init root;
    g_AppContext.setup();
    //g_AppContext.setWindowGrab(true);
    
    // create scene manager
    g_SceneManager = g_AppContext.getRoot()->createSceneManager();
    g_SceneManager->addRenderQueueListener(Ogre::OverlaySystem::getSingletonPtr());
    
    // create gui manager
    CreateGuiManager();

    // register scene manager with shader gen
    Ogre::RTShader::ShaderGenerator::getSingletonPtr()->addSceneManager(g_SceneManager);
    g_SceneManager->setAmbientLight(Ogre::ColourValue(0.5,0.5,0.5));

    CreateCameraManager();
    CreateKeypressManager();

    g_InputChain = new OgreBites::InputListenerChain({
      g_KeypressManager,
      App::GetGuiManager()->m_ImGuiInputListener.get(),
      g_CameraManager->m_CameraMan
      });

    App::GetAppContext()->addInputListener(g_InputChain);
 
    
    g_AppContext.createDummyScene();
    //CreateTestScene();

    return success;
  }

  void Close()
  {
    App::GetAppContext()->removeInputListener(g_InputChain);

    if(g_KeypressManager) delete g_KeypressManager;
    if(g_CameraManager) delete  g_CameraManager;
    if(g_GuiManager) delete g_GuiManager;

    g_AppContext.closeApp();
  }

  void StartRendering()
  {
    g_AppContext.getRoot()->startRendering();
  }


void CreateTestScene()
{
  using namespace Ogre;
  SceneNode* rootNode = g_SceneManager->getRootSceneNode();

  // scene setup
  g_SceneManager->setAmbientLight(ColourValue(0,0,0));
  g_SceneManager->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

  // without light we would just get a black screen    
  
  /*
  Light* light = g_SceneManager->createLight("MainLight");
  SceneNode* lightNode = rootNode->createChildSceneNode();
  lightNode->setPosition(0, 10, 15);
  lightNode->attachObject(light);
  */
 
  // render some ogres
  Entity* ogre1 = g_SceneManager->createEntity("ogrehead.mesh");
  ogre1->setCastShadows(true);
  SceneNode* ogreNode = rootNode->createChildSceneNode();
  ogreNode->setPosition(0, 50, 0);
  ogreNode->setScale(2, 1.2, 1);
  ogreNode->attachObject(ogre1);
  
  /*
  Entity* ogre2 = g_SceneManager->createEntity("ogrehead.mesh");
  SceneNode* ogre2Node = ogreNode->createChildSceneNode(Vector3(50, 50, 0));
  ogre2Node->setScale(2, 1.2, 1);
  ogre2Node->attachObject(ogre2);
  */
  
  Plane plane(Vector3::UNIT_Y, 0);
  MeshManager::getSingleton().createPlane(
    "Ground", RGN_DEFAULT,
    plane,
    1500, 1500, 20, 20,
    true,
    1, 5, 5,
    Vector3::UNIT_Z);
  
  Entity* groundEntity = g_SceneManager->createEntity("Ground");
  rootNode->createChildSceneNode()->attachObject(groundEntity);
  
  groundEntity->setCastShadows(false);
  groundEntity->setMaterialName("Examples/Rockwall");
  
  Light* spotlight = g_SceneManager->createLight("Spotlight");
  spotlight->setType(Light::LT_SPOTLIGHT);

  spotlight->setDiffuseColour(0, 0, 1.0);
  spotlight->setSpecularColour(0, 0, 1.0);
  spotlight->setSpotlightRange(Degree(35), Degree(50));
  
  SceneNode* spotlightNode = rootNode->createChildSceneNode();
  spotlightNode->attachObject(spotlight);
  spotlightNode->setDirection(-1, -1, 0);
  spotlightNode->setPosition(200, 200, 0);
  
  // add directional light to face
  Light* directionalLight = g_SceneManager->createLight("DirectionalLight");
  directionalLight->setType(Light::LT_DIRECTIONAL);

  directionalLight->setDiffuseColour(0.2, 0, 0);
  directionalLight->setSpecularColour(0.2, 0, 0);
  
  SceneNode* directionalLightNode = rootNode->createChildSceneNode();
  directionalLightNode->attachObject(directionalLight);
  directionalLightNode->setDirection(0, -1, 1);

  // add point light to face
  Light* pointLight = g_SceneManager->createLight("pointLight");
  pointLight->setType(Light::LT_POINT);

  pointLight->setDiffuseColour(0.5, 0.7, 0.5);
  pointLight->setSpecularColour(0.5, 0.7, 0.5);
  
  SceneNode* pointLightNode = rootNode->createChildSceneNode();
  pointLightNode->attachObject(pointLight);
  pointLightNode->setPosition(0, 20, 150);

  /*
  Ogre::ResourceGroupManager* resGrpMgr = new Ogre::ResourceGroupManager();
  resGrpMgr->
  Ogre::ResourceManager::addResourceLocation("../res", "");
  resMgr->initialiseAllResourceGroups();
  */
}
}