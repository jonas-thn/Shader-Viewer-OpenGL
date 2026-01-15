#pragma once

#include "../Scene.h"
#include "../../MeshData.h"
#include <vector>

class Application;

class PlanetScene : public Scene
{
public:
    PlanetScene() = default;
    virtual ~PlanetScene() = default;

    void Init() override;
    void Update(float dt) override;
    void Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time) override;

    std::string GetName() const override { return "Planet"; }
    void OnActivate(Application* app) override;
    void OnGuiRender() override;

private:
    Shader planetShader = Shader("./Shader/Planet/planetShader.vert", "./Shader/Planet/planetShader.frag");

    Mesh screen = Mesh(
        std::vector<float>(std::begin(screenVertices), std::end(screenVertices)),
        {}
    );
};