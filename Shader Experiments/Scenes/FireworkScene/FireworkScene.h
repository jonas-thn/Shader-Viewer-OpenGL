#pragma once

#include "../Scene.h"
#include "../../MeshData.h"
#include <vector>

class Application;

class FireworkScene : public Scene
{
public:
    FireworkScene() = default;
    virtual ~FireworkScene() = default;

    void Init() override;
    void Update(float dt) override;
    void Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time) override;

    std::string GetName() const override { return "Firework"; }
    void OnActivate(Application* app) override;
    void OnGuiRender() override;

private:
    Shader fireworkShader = Shader("./Shader/Firework/fireworkShader.vert", "./Shader/Firework/fireworkShader.frag");

    Mesh screen = Mesh(
        std::vector<float>(std::begin(screenVertices), std::end(screenVertices)),
        {}
    );
};