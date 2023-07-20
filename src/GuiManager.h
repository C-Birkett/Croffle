#pragma once

#include <Ogre.h>
#include <OgreImGuiOverlay.h>
#include <OgreRenderTargetListener.h>
#include <OgreImGuiInputListener.h>
#include <memory>

class GuiManager : public Ogre::RenderTargetListener
{
public:
    GuiManager() = default;
    ~GuiManager();
    
    Ogre::ImGuiOverlay* m_ImGuiOverlay;
    std::unique_ptr<OgreBites::ImGuiInputListener> m_ImGuiInputListener;

    void Init();
    void preViewportUpdate(const Ogre::RenderTargetViewportEvent& evt) override;
};