#pragma once

#include <Ogre.h>
#include <OgreInput.h>

class KeypressManager : public OgreBites::InputListener
{
public:
    KeypressManager() = default;
    ~KeypressManager() = default;
    
    bool keyPressed(const OgreBites::KeyboardEvent& event);
};