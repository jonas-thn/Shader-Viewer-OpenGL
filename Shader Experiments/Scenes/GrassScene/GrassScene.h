#pragma once

#include "../Scene.h"
#include "../../Shader.h"
#include "../../Mesh.h"
#include <vector>

class Application; 

class GrassScene : public Scene
{
public:
    GrassScene() = default;
    virtual ~GrassScene() = default;

    void Init() override;
    void Update(float dt) override;
    void Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time) override;

    std::string GetName() const override { return "Grass"; }
    void OnActivate(ICameraControl* cameraControl) override;
    void OnGuiRender() override;

private:
    Shader standardShader = Shader("./Shader/Standard/standardShader.vert", "./Shader/Standard/standardShader.frag");
    Shader grassShader = Shader("./Shader/Grass/grassShader.vert", "./Shader/Grass/grassShader.frag");

    Mesh plane = Mesh("./Models/quad.obj");
    Mesh sphere = Mesh("./Models/sphere.obj");

    Mesh grass1 = Mesh("./Models/grass.obj");
    Mesh grass2 = Mesh("./Models/grass.obj");
    int count = 900;
};