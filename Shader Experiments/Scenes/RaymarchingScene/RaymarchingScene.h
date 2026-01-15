#pragma once

#include "../Scene.h"
#include "../../MeshData.h"
#include <vector>

class Application;

class RaymarchingScene : public Scene
{
public:
    RaymarchingScene() = default;
    virtual ~RaymarchingScene() = default;

    void Init() override;
    void Update(float dt) override;
    void Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time) override;

    std::string GetName() const override { return "Raymarching"; }
    void OnActivate(Application* app) override;
    void OnGuiRender() override;

private:
    Shader raymarchShader = Shader("./Shader/Raymarching/raymarchShader.vert", "./Shader/Raymarching/raymarchShader.frag");

    Mesh screen = Mesh(
        std::vector<float>(std::begin(screenVertices), std::end(screenVertices)),
        {}
    );
};