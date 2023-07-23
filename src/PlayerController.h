#pragma once

#include <Ogre.h>
#include <OgreInput.h>

class Camera;

// borrowed mostly from cameraman
class PlayerController : public OgreBites::InputListener
{
public:
    PlayerController();
    ~PlayerController();

    void Init();
    void SetCamera(Camera* camera){m_Camera = camera;}

    // overloads
    void frameRendered(const Ogre::FrameEvent& evt) override;

    bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
    bool keyReleased(const OgreBites::KeyboardEvent& evt) override;
    bool mouseMoved(const OgreBites::MouseMotionEvent& evt) override;

private:
    Camera* m_Camera;

    Ogre::Real m_TopSpeed = 350;
    Ogre::Vector3 m_Velocity;

    bool m_GoingForward;
    bool m_GoingBack;
    bool m_GoingLeft;
    bool m_GoingRight;
    bool m_GoingUp;
    bool m_GoingDown;
    bool m_FastMove;

};