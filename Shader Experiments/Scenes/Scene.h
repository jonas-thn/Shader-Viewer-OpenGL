#pragma once

#include <vector>
#include <string> 
#include <glm/glm.hpp> 
#include "../Shader.h"
#include "../Mesh.h"
#include "../ICameraControl.h"

class Application;

class Scene
{
public:
    virtual ~Scene() = default;

    virtual void Init() = 0;
    virtual void Update(float dt) = 0;

    virtual void Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time) = 0;

    virtual std::string GetName() const = 0;

    virtual void OnGuiRender() {}

    virtual void OnActivate(ICameraControl* cameraControl) {}

protected:
    std::vector<Mesh*> meshList;
};