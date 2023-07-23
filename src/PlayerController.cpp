#include "PlayerController.h"

#include <Ogre.h>
#include <OgreInput.h>

#include "Camera.h"

PlayerController::PlayerController() :
m_Camera(nullptr),
m_Velocity(0,0,0),
m_GoingForward(false),
m_GoingBack(false),
m_GoingLeft(false),
m_GoingRight(false),
m_GoingUp(false),
m_GoingDown(false),
m_FastMove(false)
{

}

PlayerController::~PlayerController()
{

}

void PlayerController::Init()
{

}

// overrides

void PlayerController::frameRendered(const Ogre::FrameEvent& evt)
{
    using namespace OgreBites;
    // build our acceleration vector based on keyboard input composite
    Ogre::Vector3 accel = Ogre::Vector3::ZERO;
    Ogre::Matrix3 axes = m_Camera->getLocalAxes();

    /*
    if (m_GoingForward) accel -= axes.GetColumn(2);
    if (m_GoingBack) accel += axes.GetColumn(2);
    if (m_GoingRight) accel += axes.GetColumn(0);
    if (m_GoingLeft) accel -= axes.GetColumn(0);
    if (m_GoingUp) accel += axes.GetColumn(1);
    if (m_GoingDown) accel -= axes.GetColumn(1);
    */

    if (m_GoingForward) accel[0] -= 1;
    if (m_GoingBack) accel[0] += 1;
    if (m_GoingRight) accel[1] += 1;
    if (m_GoingLeft) accel[1] -= 1;
    if (m_GoingUp) accel[2] += 1;
    if (m_GoingDown) accel[2] -= 1;

    // if accelerating, try to reach top speed in a certain time
    Ogre::Real topSpeed = m_FastMove ? m_TopSpeed * 20 : m_TopSpeed;
    if (accel.squaredLength() != 0)
    {
        accel.normalise();
        //m_Velocity += accel * topSpeed * evt.timeSinceLastFrame * 10;
        m_Velocity = accel * topSpeed;
    }
    // if not accelerating, try to stop in a certain time
    else m_Velocity -= m_Velocity * evt.timeSinceLastFrame * 10;

    Ogre::Real tooSmall = std::numeric_limits<Ogre::Real>::epsilon();

    // keep camera velocity below top speed and above epsilon
    if (m_Velocity.squaredLength() > topSpeed * topSpeed)
    {
        m_Velocity.normalise();
        m_Velocity *= topSpeed;
    }
    else if (m_Velocity.squaredLength() < tooSmall * tooSmall)
    {
        m_Velocity = Ogre::Vector3::ZERO;
    }

    if (m_Velocity != Ogre::Vector3::ZERO) m_Camera->Translate(m_Velocity * evt.timeSinceLastFrame);

    InputListener::frameRendered(evt);
}

bool PlayerController::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    using namespace OgreBites;
    Keycode key = evt.keysym.sym;

    if (key == 'w' || key == SDLK_UP) m_GoingForward = true;
    else if (key == 's' || key == SDLK_DOWN) m_GoingBack = true;
    else if (key == 'a' || key == SDLK_LEFT) m_GoingLeft = true;
    else if (key == 'd' || key == SDLK_RIGHT) m_GoingRight = true;
    else if (key == SDLK_PAGEUP) m_GoingUp = true;
    else if (key == SDLK_PAGEDOWN) m_GoingDown = true;
    else if (key == SDLK_LSHIFT) m_FastMove = true;

    return InputListener::keyPressed(evt);
}

bool PlayerController::keyReleased(const OgreBites::KeyboardEvent& evt)
{
    using namespace OgreBites;
    Keycode key = evt.keysym.sym;

    if (key == 'w' || key == SDLK_UP) m_GoingForward = false;
    else if (key == 's' || key == SDLK_DOWN) m_GoingBack = false;
    else if (key == 'a' || key == SDLK_LEFT) m_GoingLeft = false;
    else if (key == 'd' || key == SDLK_RIGHT) m_GoingRight = false;
    else if (key == SDLK_PAGEUP) m_GoingUp = false;
    else if (key == SDLK_PAGEDOWN) m_GoingDown = false;
    else if (key == SDLK_LSHIFT) m_FastMove = false;

    return InputListener::keyReleased(evt);
}

bool PlayerController::mouseMoved(const OgreBites::MouseMotionEvent& evt)
{
    m_Camera->Yaw(Ogre::Degree(-evt.xrel * 0.15f));
    m_Camera->Pitch(Ogre::Degree(-evt.yrel * 0.15f));

    return InputListener::mouseMoved(evt);
}