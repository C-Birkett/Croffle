#include "GuiManager.h"

#include <Ogre.h>
#include <OgreApplicationContextBase.h>
#include <OgreFrameListener.h>
#include <OgreImGuiInputListener.h>
#include <OgreImGuiOverlay.h>
#include <OgreRenderTargetListener.h>
#include <OgreResourceGroupManager.h>
#include <OgreFont.h>
#include <OgreFontManager.h>
#include <OgreOverlayManager.h>
#include <OgreOverlaySystem.h>
#include <OgreTrays.h>
#include <imgui.h>

#include "Application.h"

GuiManager::~GuiManager()
{
    Ogre::OverlayManager::getSingletonPtr()->destroy("ImGuiOverlay");
    App::GetAppContext()->getRenderWindow()->removeListener(this);
}

void GuiManager::Init()
{
    /*
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/home/conan/Work/OgreTest/res/fonts", "FileSystem", "FONTS", true);
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("FONTS");
    Ogre::ResourceGroupManager::getSingleton().loadResourceGroup("FONTS");
    Ogre::FontPtr font = Ogre::FontManager::getSingleton().getByName("CozetteVector");
    */

    m_ImGuiOverlay = new Ogre::ImGuiOverlay();
    
    //m_ImGuiOverlay->addFont("CozetteVector", "FONTS");
    m_ImGuiOverlay->setZOrder(300);
    m_ImGuiOverlay->show();
    
    Ogre::OverlayManager::getSingletonPtr()->addOverlay(m_ImGuiOverlay);

    App::GetAppContext()->getRenderWindow()->addListener(this);
    
    m_ImGuiInputListener.reset(new OgreBites::ImGuiInputListener());
}

void GuiManager::preViewportUpdate(const Ogre::RenderTargetViewportEvent& evt)
{
    if(!evt.source->getOverlaysEnabled()) return;

    Ogre::ImGuiOverlay::NewFrame();
    ImGui::ShowDemoWindow();
}


