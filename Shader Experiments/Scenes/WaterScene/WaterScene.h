#pragma once

#include "../Scene.h"
#include "../../MeshData.h"
#include <vector>

class Application;

class WaterScene : public Scene
{
public:
    WaterScene() = default;
    virtual ~WaterScene() = default;

    void Init() override;
    void Update(float dt) override;
    void Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time) override;

    std::string GetName() const override { return "Water"; }
    void OnActivate(ICameraControl* cameraControl) override;
    void OnGuiRender() override;

private:
    Shader waterShader = Shader("./Shader/Water/waterShader.vert", "./Shader/Water/waterShader.frag");

    Mesh screen = Mesh(
        std::vector<float>(std::begin(screenVertices), std::end(screenVertices)),
        {}
    );
};