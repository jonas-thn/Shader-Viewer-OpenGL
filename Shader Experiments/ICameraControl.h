#pragma once

class ICameraControl
{
public:
    virtual ~ICameraControl() = default;

    virtual void SetCameraConfig(float radius, float speed, float height) = 0;
};