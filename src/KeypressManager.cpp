#include "KeypressManager.h"

#include <Ogre.h>
#include <OgreInput.h>

#include "Application.h"
#include "GuiManager.h"

bool KeypressManager::keyPressed(const OgreBites::KeyboardEvent& event)
{
  switch (event.keysym.sym) 
  {
    case OgreBites::SDLK_ESCAPE:
    {
      App::GetAppContext()->getRoot()->queueEndRendering();
      return true;
    }
    case OgreBites::SDLK_SPACE:
    {
      auto overlay = App::GetGuiManager()->m_ImGuiOverlay;

      overlay->setVisible(!overlay->isVisible());

      return true;
    }
    default:
    return false;
  }
}
