#pragma once

class Camera;

class CameraManager
{
public:
    CameraManager();
    ~CameraManager();
    
    Camera*       m_Camera;

    void Init();
};